// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestStep.h"
#include "QuestGraphRuntime.generated.h"


/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestGraphRuntimePin : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FName pinName;
	
	UPROPERTY()
	FGuid pinID;
	
	UPROPERTY()
	UQuestGraphRuntimePin* connection = nullptr;
	
	UPROPERTY()
	UQuestGraphRuntimeNode* parent = nullptr;
};

UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestGraphRuntimeNode : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UQuestGraphRuntimePin*> InputPin;
	
	UPROPERTY()
	TArray<UQuestGraphRuntimePin*> OutputPins;
	
	UPROPERTY()
	FVector2D position;
	
	UPROPERTY()
	UQuestStep* nodeClass = nullptr;
};

UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestGraphRuntimeGraph : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UQuestGraphRuntimeNode*> Nodes;
	
};