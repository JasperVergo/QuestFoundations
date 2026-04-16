// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestRunner.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubsystem.generated.h"



/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UQuestSubsystem();
	
public:
	
	void AddNewQuest(UQuestAsset* questAsset, APlayerController* owningPlayer);
	void FinishQuest(UQuestRunner::EQuestFinishState finishState);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void setWorldContext(UWorld* context);
	
	
	private:
	UPROPERTY()
	TArray<UQuestRunner*> _activeQuests;
	
	UPROPERTY()
	UWorld* _worldContext = nullptr;
};
