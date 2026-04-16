// Fill out your copyright notice in the Description page of Project Settings.
#include "TestPlayerController.h"
#include "QuestAsset.h"
#include "QuestSubsystem.h"


#include "QuestSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(TestPlayerControllerSub, Log, All);

ATestPlayerController::ATestPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UQuestAsset> questAssetFinder(TEXT("/Game/NewQuestAsset"));
	if (questAssetFinder.Succeeded()) {
		_questAsset = questAssetFinder.Object;
		UE_LOG(TestPlayerControllerSub, Log, TEXT("Loaded quest Asset"));
	} else {
		UE_LOG(TestPlayerControllerSub, Error, TEXT("Could not load content"));
	}
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Play the dialog
	_questSubsystem = GetGameInstance()->GetSubsystem<UQuestSubsystem>();
	if (_questAsset != nullptr) {
		_questSubsystem->AddNewQuest(_questAsset, this);
	}
}
