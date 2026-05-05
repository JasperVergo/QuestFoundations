// Fill out your copyright notice in the Description page of Project Settings.
#include "TestPlayerController.h"
#include "QuestAsset.h"
#include "QuestSubsystem.h"


#include "QuestSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(TestPlayerControllerSub, Log, All);

ATestPlayerController::ATestPlayerController()
{
	
	
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Play the dialog
	_questSubsystem = GetGameInstance()->GetSubsystem<UQuestSubsystem>();
	if (GetWorld() == nullptr)
	{
		UE_LOG(TestPlayerControllerSub, Error, TEXT("World context is null"));
	}
	_questSubsystem->setWorldContext(GetWorld());
	_questSubsystem->startQuest(TEXT("/Game/NewQuestAsset"), this);
}
