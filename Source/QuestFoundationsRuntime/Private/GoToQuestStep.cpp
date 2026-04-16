// Fill out your copyright notice in the Description page of Project Settings.


#include "GoToQuestStep.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(QuestStepSub, Log, All)

void UGoToQuestStep::InitQuestStep()
{
	nodeToolTip = FText::FromString(TEXT("Quests"));
	nodeName = FText::FromString(TEXT("Go To Location"));
	nodeToolTip = FText::FromString(TEXT("Requires the player to go to a specified location"));
	inputPins = {"start"};
	outputPins = {"Continue", "Reached"};
	UE_LOG(LogTemp, Display, TEXT("set up GoTO pin"));
}

void UGoToQuestStep::BeginQuestStep()
{
	Super::BeginQuestStep();
	SendOutput(0, false);
	_playerRef = UGameplayStatics::GetPlayerCharacter(worldContext,0);
	
}

void UGoToQuestStep::TickQuestStep(float DeltaTime)
{
	Super::TickQuestStep(DeltaTime);
	if (_playerRef == nullptr)
	{
		if (worldContext == nullptr)
		{
			UE_LOG(QuestStepSub, Error, TEXT("world context is nullptr"));
			return;
		}
		UE_LOG(QuestStepSub, Error, TEXT("Player Ref is nullptr"));
		_playerRef = UGameplayStatics::GetPlayerCharacter(worldContext,0);
		return;	
	}
	
	if (FVector::Distance(_playerRef->GetActorLocation(), locationToGoTo) <= tolerance)
	{
		UE_LOG(QuestStepSub, Log, TEXT("Player Reached GOTO location"));
		SendOutput(1, true);
	}
	
}
