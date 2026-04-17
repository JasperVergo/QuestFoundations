// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestStepGraphNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"
#include "QuestStep.h"

UQuestStepGraphNode::UQuestStepGraphNode()
{}

FText UQuestStepGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return _questStep->GetNodeName();
}

void UQuestStepGraphNode::GetNodeContextMenuActions(class UToolMenu* menu,
                                                    class UGraphNodeContextMenuContext* context) const
{
	FToolMenuSection& section = menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Quest Node Actions")));
	
	//TODO: Just all of this has to go at some point or at least the lambda
	
	UQuestStepGraphNode* node = (UQuestStepGraphNode*)this;
	section.AddMenuEntry(
TEXT("DeleteNode"),
FText::FromString(TEXT("Delete Nodde")),
FText::FromString(TEXT("Deletes the Node")),
FSlateIcon(TEXT("QuestFoundationsEditorStyle"), TEXT("QuestFoundations.NodeDeleteNodeIcon")),
	
FUIAction(FExecuteAction::CreateLambda(
	[node](){
		
		node->GetGraph()->RemoveNode(node);
		}
	))
);
}

UEdGraphPin* UQuestStepGraphNode::CreateQuestPin(EEdGraphPinDirection direction, FName name)
{
	FName category = (direction == EEdGraphPinDirection::EGPD_Input) ? TEXT("Input") : TEXT("Output");
	FName subCategory = TEXT("QuestPin");
	
	UEdGraphPin* pin = this->CreatePin(
		direction,
		category,
		name
	);
	pin->PinType.PinSubCategory = subCategory;
	
	return pin;
}

