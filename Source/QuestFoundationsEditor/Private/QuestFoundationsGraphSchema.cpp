// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestFoundationsGraphSchema.h"

#include "ExsampleQuestStep.h"
#include "QuestStepGraphNode.h"
#include "QuestStep.h"



void UQuestFoundationsGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const
{
	
	TArray<UClass*> nodeClasses;
	GetDerivedClasses(UQuestStep::StaticClass(), nodeClasses, true);
	nodeClasses.Add(UQuestStep::StaticClass());
	//nodeClasses.Add(UExsampleQuestStep::StaticClass());
	//TODO: Replace with template that dose this automatically 
	
	for (UClass* nodeClass : nodeClasses)
	{
		UQuestStep* objDefaults = NewObject<UQuestStep>(nodeClass, nodeClass);
		objDefaults->InitQuestStep();
		
		TSharedPtr<FNewNodeAction> newNodeAction(
			new FNewNodeAction(
				nodeClass, //class
				objDefaults->GetNodeCategory(), //Catigory
				objDefaults->GetNodeName(), //Node Name
				objDefaults->GetNodeToolTip(), //tooltip
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

void UQuestFoundationsGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	Super::CreateDefaultNodesForGraph(Graph);
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2D location,
                                            bool bSelectNewNode)
{
	//createing a new node
	UQuestStepGraphNode* result = NewObject<UQuestStepGraphNode>(parentGraph);
	result->CreateNewGuid();
	result->NodePosX = location.X;
	result->NodePosY = location.Y;
	result->setNodeClass(NewObject<UQuestStep>(result, nodeType));
	
	UEdGraphPin* inputPin = nullptr;

	if (IsValid(result->getNodeClass()) )
	{
		UE_LOG(LogTemp, Display, TEXT("Created pins: %d"), result->getNodeClass()->GetOutputPins().Num());
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Class"));
	}
	
	
	for (FName name : result->getNodeClass()->GetInputPins())
	{
		inputPin = result->CreateQuestPin(EGPD_Input, name);
	}
	for (FName name : result->getNodeClass()->GetOutputPins())
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
