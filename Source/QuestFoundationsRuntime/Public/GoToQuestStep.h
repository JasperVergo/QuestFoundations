// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestStep.h"
#include "GoToQuestStep.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UGoToQuestStep : public UQuestStep
{
	GENERATED_BODY()
	
public:
	virtual void InitQuestStep() override;
	virtual void BeginQuestStep() override;
	virtual void TickQuestStep(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere)
	FVector locationToGoTo = FVector(0.0f, 0.0f, 0.0f);	
	
	UPROPERTY(EditAnywhere)
	float tolerance = 500.0f;
	
	private:
	UPROPERTY()
	class ACharacter* _playerRef = nullptr;
};


