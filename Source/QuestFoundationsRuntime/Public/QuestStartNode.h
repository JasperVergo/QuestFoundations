// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStep.h"
#include "QuestStartNode.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestStartNode : public UQuestStep
{
	GENERATED_BODY()
	
	
	public:
	
	virtual void InitQuestStep() override;
	
	virtual void BeginQuestStep() override;
	virtual void EndQuestStep() override {}
	virtual void TickQuestStep(float DeltaTime) override {}
	virtual void ResievedInput(int inputPinIndex) override {}
	virtual void SendOutput(int outPinIndex, bool endCurrentNode = false) override {}
};
