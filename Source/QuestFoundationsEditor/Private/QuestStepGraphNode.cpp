// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestStepGraphNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

UQuestStepGraphNode::UQuestStepGraphNode()
{
	_workingquestStep = NewObject<UQuestStep>();
	
	//TODO: depricate this variables and use the _workingquestStep directly
	inputPins = _workingquestStep->GetInputPins();
	outputPins = _workingquestStep->GetOutputPins();
}

void UQuestStepGraphNode::GetNodeContextMenuActions(class UToolMenu* menu,
                                                    class UGraphNodeContextMenuContext* context) const
{
	FToolMenuSection& section = menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Quest Node Actions")));
	
	//TODO: Just all of this has to go at some point or at least the lambda
	
	UQuestStepGraphNode* node = (UQuestStepGraphNode*)this;
	section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Pin")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(TEXT("QuestFoundationsEditorStyle"), TEXT("QuestFoundations.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[node](){
				
				node->CreateQuestPin(EEdGraphPinDirection::EGPD_Output, TEXT("Another one"));
				
				node->GetGraph()->NotifyGraphChanged();
				node->GetGraph()->Modify();
				
			}
		))
	);
	section.AddMenuEntry(
	TEXT("DeletePinEntry"),
	FText::FromString(TEXT("Delete Pin")),
	FText::FromString(TEXT("Deletes the last pin")),
	FSlateIcon(TEXT("QuestFoundationsEditorStyle"), TEXT("QuestFoundations.NodeDeleteIcon")),
	
	FUIAction(FExecuteAction::CreateLambda(
		[node](){
			UEdGraphPin* pin = node->GetPinAt(node->Pins.Num() - 1);
			if (pin->Direction != EEdGraphPinDirection::EGPD_Input)
			{
				node->RemovePin(pin);
				
				node->GetGraph()->NotifyGraphChanged();
				node->GetGraph()->Modify();
			}
				
			}
		))
	);
	
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

