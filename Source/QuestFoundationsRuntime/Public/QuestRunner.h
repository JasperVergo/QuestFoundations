// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestRunner.generated.h"




/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestRunner : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
	public:
	
	enum class EQuestFinishState : uint8
	{
		Complete,
		Cancelled,
		Failed,
		Botched,
	};
	UFUNCTION()
	void RunQuest(class UQuestAsset* QuestAsset, APlayerController* owningPlayer);
	
	void AdvanceQuestByIndexWithStop(class UQuestGraphRuntimeNode* node, int outputPinIndex, bool stopRunningExitNode);
	UFUNCTION()
	void AdvanceQuestByIndex(class UQuestGraphRuntimeNode* node, int outputPinIndex);
	UFUNCTION()
	void AddRunningNode(class UQuestGraphRuntimeNode* node);
	UFUNCTION()
	void RemoveRunningNodeByNode(class UQuestGraphRuntimeNode* node);
	UFUNCTION()
	void RemoveRunningNode(class UQuestStep* step);
	UFUNCTION()
	void TickRunningNodes(float DeltaTime);
	void SetWorldContext(UWorld* context);
	
	
	virtual void Tick(float DeltaTime) override;
	
	bool IsTickable() const override;
	TStatId GetStatId() const override;
	ETickableTickType GetTickableTickType() const override;

	
	
	private:
	
	UPROPERTY()
	UWorld* worldContext = nullptr;
	
	UPROPERTY()
	class UQuestAsset* _questAsset = nullptr;
	
	UPROPERTY()
	TArray<class UQuestGraphRuntimeNode*> _runningNodes; 
	
	UPROPERTY()
	class UQuestGraphRuntimeGraph* _questGraph = nullptr;
	
	
	
};
