// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestRunner.h"
#include "QuestAsset.h" 
#include "QuestStep.h"
#include "QuestStartNode.h"
#include "QuestGraphRuntime.h"

DEFINE_LOG_CATEGORY_STATIC(QuestPlayerSub, Log, All)

void UQuestRunner::RunQuest(UQuestAsset* QuestAsset, APlayerController* owningPlayer)
{
	_questAsset = QuestAsset;
	_questGraph = QuestAsset->graph;
	
	//find first node 
	for (UQuestGraphRuntimeNode* node : _questGraph->Nodes)
	{
		if (Cast<UQuestStartNode>(node->nodeClass))
		{
			AddRunningNode(node);
			break;
		}
	}
	
	if (_runningNodes.Num() <= 0 || _runningNodes[0] == nullptr)
	{
		UE_LOG(QuestPlayerSub, Error, TEXT("No start node found in quest graph"));
		return;
	}
	
	AdvanceQuestByIndex(_runningNodes[0], 0, true);
	
}

void UQuestRunner::AdvanceQuestByIndex(class UQuestGraphRuntimeNode* node, int outputPinIndex, bool stopRunningExitNode)
{
	if (outputPinIndex >= node->OutputPins.Num() || outputPinIndex < 0)
	{
		UE_LOG(QuestPlayerSub, Error, TEXT("Output pin index out of bounds at index %d"), outputPinIndex);
		return;
	}
	
	UQuestGraphRuntimePin* outputPin = node->OutputPins[outputPinIndex];
	if (outputPin->connection == nullptr)
	{
		UE_LOG(QuestPlayerSub, Error, TEXT("Output pin %s has no connection recommend adding a end quest node here"), *outputPin->pinName.ToString());
		return;
	} else
	{
		AddRunningNode(outputPin->connection->parent);
	}
	if (stopRunningExitNode)
	{
		RemoveRunningNode(node);
	}
	
	
	
}

void UQuestRunner::AddRunningNode(class UQuestGraphRuntimeNode* node)
{
	_runningNodes.Add(node);
	node->nodeClass->BeginQuestStep();
	node->nodeClass->OnQuestStepEnd.AddDynamic(this, &UQuestRunner::RemoveRunningNode);
}

void UQuestRunner::RemoveRunningNode(class UQuestGraphRuntimeNode* node)
{
	_runningNodes.Remove(node);
	node->nodeClass->EndQuestStep();
}

void UQuestRunner::RemoveRunningNode(UQuestStep* step)
{
	for (int i = 0; i < _runningNodes.Num(); i++)
	{
		if (_runningNodes[i]->nodeClass == step)
		{
			RemoveRunningNode(_runningNodes[i]);
			return;
		}
	}
}

void UQuestRunner::TickRunningNodes(float DeltaTime)
{
	for (UQuestGraphRuntimeNode* node : _runningNodes)
	{
		node->nodeClass->TickQuestStep(DeltaTime);
	}
}

void UQuestRunner::Tick(float DeltaTime)
{
	TickRunningNodes(DeltaTime);
}
