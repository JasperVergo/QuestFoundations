// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"
#include "QuestAsset.h"

DEFINE_LOG_CATEGORY_STATIC(QuestSubsyetemSub, Log, All)

UQuestSubsystem::UQuestSubsystem()
{

}

void UQuestSubsystem::AddNewQuest(UQuestAsset* questAsset, APlayerController* owningPlayer)
{
	UQuestRunner* newQuest = NewObject<UQuestRunner>();
	_activeQuests.Add(newQuest);
	newQuest->RunQuest(questAsset, owningPlayer);
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
