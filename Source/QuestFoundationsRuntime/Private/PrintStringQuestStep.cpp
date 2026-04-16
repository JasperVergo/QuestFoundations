// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintStringQuestStep.h"

DEFINE_LOG_CATEGORY_STATIC(QuestStepSub, Log, All)

void UPrintStringQuestStep::InitQuestStep()
{
	nodeToolTip = FText::FromString(TEXT("Debug"));
	nodeName = FText::FromString(TEXT("Print String"));
	nodeToolTip = FText::FromString(TEXT("Prints a string to the screen when this step is reached"));
	inputPins = {"Print"};
	outputPins = {"Continue"};
	UE_LOG(LogTemp, Display, TEXT("set up Print pin"));
}

void UPrintStringQuestStep::BeginQuestStep()
{
	Super::BeginQuestStep();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::White, stringToPrint);
	}
	UE_LOG(LogTemp, Display, TEXT("%s"), *stringToPrint);
	
	SendOutput(0);
}

void UPrintStringQuestStep::EndQuestStep()
{
	Super::EndQuestStep();
}

void UPrintStringQuestStep::SendOutput(int outputIndex, bool endCurrentNode)
{
	UE_LOG(QuestStepSub, Display, TEXT("Sent Output front %s"), *nodeName.ToString());
	Super::SendOutput(outputIndex, endCurrentNode);
}
