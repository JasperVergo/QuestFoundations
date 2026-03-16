// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestStep.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestStep : public UObject
{
	GENERATED_BODY()

	public:
	//TODO: Virtual destructor
	UQuestStep(FText catagory, FText name, FText tooltip) : nodeCatagory{catagory}, nodeName{name}, nodeToolTip{tooltip}
	{
		AddInputOutputPins();
	}
	
	UQuestStep() : UQuestStep(
		FText::FromString(TEXT("Quests")),
		FText::FromString(TEXT("Add Quest Step")),
		FText::FromString(TEXT("Adds a new quest step to the graph"))) {}
	
	virtual TArray<FName> GetInputPins() {return inputPins;}
	virtual TArray<FName> GetOutputPins() {return outputPins;}
	virtual FText& GetNodeName() {return nodeName;}
	virtual FText& GetNodeToolTip() {return nodeToolTip;}
	virtual FText& GetNodeCategory() {return nodeCatagory;}
	
	
	
	protected:
	
	virtual void AddInputOutputPins()
	{
		inputPins.Add("Default Input");
		outputPins.Add("Default Output");
		inputPins.Add("inputs 3");
	};
	

	TArray<FName> inputPins;
	

	TArray<FName> outputPins;
	
	UPROPERTY()
	FText nodeCatagory;
	
	UPROPERTY()
	FText nodeName;
	
	UPROPERTY()
	FText nodeToolTip;
	
	
};
