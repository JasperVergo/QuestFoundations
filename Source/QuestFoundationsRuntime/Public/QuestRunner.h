// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestRunner.generated.h"




/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestRunner : public UObject
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
	
	void RunQuest(class UQuestAsset* QuestAsset, APlayerController* owningPlayer);
	void AdvanceQuestByIndex(class UQuestGraphRuntimeNode* node, int outputPinIndex, bool stopRunningExitNode = false);
	void AddRunningNode(class UQuestGraphRuntimeNode* node);
	void RemoveRunningNode(class UQuestGraphRuntimeNode* node);
	void RemoveRunningNode(class UQuestStep* step);
	void TickRunningNodes(float DeltaTime);
	virtual void Tick(float DeltaTime);

	
	
	private:
	UPROPERTY()
	class UQuestAsset* _questAsset = nullptr;
	
	UPROPERTY()
	TArray<class UQuestGraphRuntimeNode*> _runningNodes; 
	
	UPROPERTY()
	class UQuestGraphRuntimeGraph* _questGraph = nullptr;
	
	
	
};
