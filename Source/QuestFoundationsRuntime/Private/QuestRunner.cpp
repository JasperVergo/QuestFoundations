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
	
	AdvanceQuestByIndexWithStop(_runningNodes[0], 0, true);
	
}

void UQuestRunner::AdvanceQuestByIndexWithStop(class UQuestGraphRuntimeNode* node, int outputPinIndex, bool stopRunningExitNode)
{
	UE_LOG(QuestPlayerSub, Log, TEXT("Started new Quest Step"));
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
		if (outputPin->connection->parent == nullptr)
		{
			UE_LOG(QuestPlayerSub, Error, TEXT("Output pin %s has no parent recommend adding a end quest node here"), *outputPin->pinName.ToString());
		}
		AddRunningNode(outputPin->connection->parent);
	}
	if (stopRunningExitNode)
	{
		RemoveRunningNodeByNode(node);
	}
	
	
	
}

void UQuestRunner::AdvanceQuestByIndex(class UQuestGraphRuntimeNode* node, int outputPinIndex)
{
	AdvanceQuestByIndexWithStop(node, outputPinIndex, false);
}

void UQuestRunner::AddRunningNode(class UQuestGraphRuntimeNode* node)
{
	UE_LOG(QuestPlayerSub, Log, TEXT("Added new running pin"));
	_runningNodes.Add(node);
	node->nodeClass->owningRunner = this;
	node->nodeClass->BeginQuestStep();
	//node->nodeClass->OnQuestStepEnd.AddDynamic(this, &UQuestRunner::RemoveRunningNode);
	if (node->nodeClass->getParent() == nullptr)
	{
		UE_LOG(QuestPlayerSub, Error, TEXT("Node Parent is null"));
	}
	//TODO: fix this idk why the deligate isn't binding
	//node->nodeClass->OnReievedOutput.AddDynamic(this, &UQuestRunner::AdvanceQuestByIndex);
}

void UQuestRunner::RemoveRunningNodeByNode(class UQuestGraphRuntimeNode* node)
{
	UE_LOG(QuestPlayerSub, Log, TEXT("Removed running pin %s"), *node->nodeClass->GetNodeName().ToString());
	_runningNodes.Remove(node);
	node->nodeClass->EndQuestStep();
}

void UQuestRunner::RemoveRunningNode(UQuestStep* step)
{
	for (int i = 0; i < _runningNodes.Num(); i++)
	{
		if (_runningNodes[i]->nodeClass == step)
		{
			RemoveRunningNodeByNode(_runningNodes[i]);
			return;
		}
	}
}

void UQuestRunner::TickRunningNodes(float DeltaTime)
{
	//TODO this runs into issues when a node is removed mid iteration 
	for (UQuestGraphRuntimeNode* node : _runningNodes)
	{
		node->nodeClass->TickQuestStep(DeltaTime);
	}
}

void UQuestRunner::SetWorldContext(UWorld* context)
{
	if (context == nullptr)
	{
		UE_LOG(QuestPlayerSub, Error, TEXT("Context is nullptr in quest player"));
	} else
	{
		UE_LOG(QuestPlayerSub, Log, TEXT("Context set in quest player"));
	}
	worldContext = context;
	for (UQuestGraphRuntimeNode* node : _questAsset->graph->Nodes)
	{
		node->nodeClass->setWorldContext(context);
	}
}

void UQuestRunner::Tick(float DeltaTime)
{
	TickRunningNodes(DeltaTime);
}

bool UQuestRunner::IsTickable() const
{
	return true;
}

TStatId UQuestRunner::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UQuestRunner, STATGROUP_Tickables);
}

ETickableTickType UQuestRunner::GetTickableTickType() const
{
	return ETickableTickType::Always;
}


