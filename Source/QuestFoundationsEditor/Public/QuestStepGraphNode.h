// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "QuestStep.h"
#include "QuestStepGraphNode.generated.h"


/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSEDITOR_API UQuestStepGraphNode : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	 
	UQuestStepGraphNode();
	
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override {return FText::FromString(TEXT("Quest Step Node")); }
	virtual FLinearColor GetNodeTitleColor() const override {return FLinearColor::Green;}
	virtual bool CanUserDeleteNode() const override {return true;}
	virtual void GetNodeContextMenuActions(class UToolMenu* menu, class UGraphNodeContextMenuContext* context) const override;
	UEdGraphPin* CreateQuestPin(EEdGraphPinDirection direction, FName name);
	TArray<FName> GetInputPins() {return inputPins;}
	TArray<FName> GetOutputPins() {return outputPins;}

	
protected:
	
	UPROPERTY()
	TArray<FName> inputPins;
	UPROPERTY()
	TArray<FName> outputPins;
	
	UPROPERTY()
	UQuestStep* _workingquestStep;
	
	
};
