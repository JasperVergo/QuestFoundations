// Fill out your copyright notice in the Description page of Project Settings.


#include "ExsampleQuestStep.h"

void UExsampleQuestStep::InitQuestStep()
{
	nodeToolTip = FText::FromString(TEXT("Quests"));
	nodeName = FText::FromString(TEXT("Another quest node"));
	nodeToolTip = FText::FromString(TEXT("This is just a test"));
	inputPins = {"input Pin"};
	outputPins = {"output Pin01", "output Pin02", "output Pin03", "output Pin04", "output Pin05"};
	UE_LOG(LogTemp, Display, TEXT("set up exsample pin"));
}
