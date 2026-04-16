// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStep.h"
#include "SequenceNodeStep.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSEDITOR_API USequenceNodeStep : public UQuestStep
{
	GENERATED_BODY()
	
public:
	virtual void InitQuestStep() override;
	virtual void BeginQuestStep() override;
	
public:
};
