// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"
#include "QuestAsset.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UObject/UObjectGlobals.h"



DEFINE_LOG_CATEGORY_STATIC(QuestSubsyetemSub, Log, All)

UQuestSubsystem::UQuestSubsystem()
{

}

void UQuestSubsystem::startQuest(FString fileName, APlayerController* controller)
{
	UQuestAsset* questAsset = nullptr;
	FString gamePath = TEXT("/Game/");
	FString filePath = gamePath + fileName;
	UE_LOG(QuestSubsyetemSub, Log, TEXT("Trying to load quest asset from path: %s"), *filePath);
	questAsset = LoadObject<UQuestAsset>(nullptr, filePath);
	
	if (questAsset != nullptr) {
		UE_LOG(QuestSubsyetemSub, Log, TEXT("Loaded quest Asset"));
		AddNewQuest(questAsset, controller);
	} else
	{
		UE_LOG(QuestSubsyetemSub, Error, TEXT("Could not load content"));
	}
}

void UQuestSubsystem::AddNewQuest(UQuestAsset* questAsset, APlayerController* owningPlayer)
{
	UQuestRunner* newQuest = NewObject<UQuestRunner>();
	_activeQuests.Add(newQuest);
	newQuest->RunQuest(questAsset, owningPlayer);
	if (_worldContext != nullptr)
	{
		for (UQuestRunner* obj : _activeQuests)
		{
			obj->SetWorldContext(_worldContext);
		}
	}
}

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UQuestSubsystem::setWorldContext(UWorld* context)
{
	if (context == nullptr)
	{
		UE_LOG(QuestSubsyetemSub, Error, TEXT("Context is nullptr in quest subsystem"));
	} else
	{
		UE_LOG(QuestSubsyetemSub, Log, TEXT("Context set in quest subsystem"));
	}
	_worldContext = context;
	for (UQuestRunner* obj : _activeQuests)
	{
		obj->SetWorldContext(context);
	}
}
