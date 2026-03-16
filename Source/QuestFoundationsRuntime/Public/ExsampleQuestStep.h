// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStep.h"
#include "ExsampleQuestStep.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UExsampleQuestStep : public UQuestStep
{
	GENERATED_BODY()
	
	public:
	UExsampleQuestStep() : UQuestStep(
		FText::FromString(TEXT("Quests")), 
		FText::FromString(TEXT("Another quest node")), 
		FText::FromString(TEXT("This is just a test")))
	{}
	
	protected:
	
	virtual void AddInputOutputPins() override
	{
		inputPins.Add("Another Input");
		outputPins.Add("Another Output");
		outputPins.Add("Another Output pt 2");
	}
};
