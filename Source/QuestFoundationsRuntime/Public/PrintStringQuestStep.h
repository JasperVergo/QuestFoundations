// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStep.h"
#include "PrintStringQuestStep.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UPrintStringQuestStep : public UQuestStep
{
	GENERATED_BODY()
	
	public:
	virtual void InitQuestStep() override;
	virtual void BeginQuestStep() override;
	virtual void EndQuestStep() override;
	virtual void SendOutput(int outputIndex, bool endCurrentNode = true) override;
	
public:
	UPROPERTY(EditAnywhere)
	FString stringToPrint = "Hello World";
	
	UPROPERTY(EditAnywhere)
	float displayTime = 5.0f;
};
