// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStep.h"
#include "NotQuestStep.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UNotQuestStep : public UQuestStep
{
	GENERATED_BODY()
	
public:
	virtual void InitQuestStep() override;
	virtual void ResievedInput(int inputPinIndex) override;
	
	
private:
	bool hasBeenNegated = false;
};
