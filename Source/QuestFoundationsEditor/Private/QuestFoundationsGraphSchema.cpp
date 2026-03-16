// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestFoundationsGraphSchema.h"

#include "ExsampleQuestStep.h"
#include "QuestStepGraphNode.h"
#include "QuestStep.h"



void UQuestFoundationsGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const
{
	TArray<UQuestStep*> nodeClasses;
	nodeClasses.Add(NewObject<UQuestStep>());
	nodeClasses.Add(NewObject<UExsampleQuestStep>());
	//TODO: Replace with template that dose this automatically 
	
	for (UQuestStep* nodeClass : nodeClasses)
	{
		
		TSharedPtr<FNewNodeAction> newNodeAction(
			new FNewNodeAction(	
				nodeClass->GetNodeCategory(), //Catigory
				nodeClass->GetNodeName(), //Node Name
				nodeClass->GetNodeToolTip(), //tooltip
				0 //group 
			)
		);
		
		contextMenuBuilder.AddAction(newNodeAction);
	}
}

const FPinConnectionResponse UQuestFoundationsGraphSchema::CanCreateConnection(const UEdGraphPin* a,
	const UEdGraphPin* b) const
{
	if (a == nullptr || b == nullptr) {
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
	}
	if (a->Direction == b->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
	}
	
	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2D location,
                                            bool bSelectNewNode)
{
	//createing a new node
	UQuestStepGraphNode* result = NewObject<UQuestStepGraphNode>(parentGraph);
	result->CreateNewGuid();
	result->NodePosX = location.X;
	result->NodePosY = location.Y;
	UEdGraphPin* inputPin = nullptr;
	//TODO: Make this dynamic based on the node
	for (FName name : result->GetInputPins())
	{
		inputPin = result->CreateQuestPin(EGPD_Input, name);
	}
	for (FName name : result->GetOutputPins())
	{
		result->CreateQuestPin(EGPD_Output, name);
	}
	
	
	parentGraph->Modify();
	parentGraph->AddNode(result, true, true);
	
	if (fromPin != nullptr)
	{
		result->GetSchema()->TryCreateConnection(fromPin, inputPin);
	}
	
	return result;
}
