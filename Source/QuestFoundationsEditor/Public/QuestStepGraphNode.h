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
	
public: //Graph iterface
	 
	UQuestStepGraphNode();
	
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override {return FLinearColor::Green;}
	virtual bool CanUserDeleteNode() const override {return true;}
	virtual void GetNodeContextMenuActions(class UToolMenu* menu, class UGraphNodeContextMenuContext* context) const override;
	
	virtual UEdGraphPin* CreateQuestPin(EEdGraphPinDirection direction, FName name);
	virtual TArray<FName> GetInputPins() {return _questStep->GetInputPins();}
	virtual TArray<FName> GetOutputPins() {return _questStep->GetOutputPins();}
	virtual void initNodeClass() {_questStep->InitQuestStep();};
	
	virtual void onPropertiesChanged() {};

public: //User interface
	
	
	void setNodeClass(class UQuestStep* questStep)
	{
		_questStep = questStep;
		_questStep->InitQuestStep();
	}
	class UQuestStep* getNodeClass() {return _questStep;}
	

	
protected:
	
	UPROPERTY()
	class UQuestStep* _questStep = nullptr;
	
	
};
