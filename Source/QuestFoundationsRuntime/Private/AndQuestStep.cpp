// Fill out your copyright notice in the Description page of Project Settings.


#include "AndQuestStep.h"

void UAndQuestStep::InitQuestStep()
{
	Super::InitQuestStep();
	
	nodeToolTip = FText::FromString(TEXT("Quests"));
	nodeName = FText::FromString(TEXT("And"));
	nodeToolTip = FText::FromString(TEXT("Requires both a and b to continue"));
	inputPins = {"A", "B"};
	outputPins = {"Continue"};
	UE_LOG(LogTemp, Display, TEXT("set up And pin"));
}

void UAndQuestStep::ResievedInput(int inputPinIndex)
{
	Super::ResievedInput(inputPinIndex);
	
	if (inputPinIndex == 0)
	{
		resievedA = true;
	} else
	{
		resievedB = true;
	}
	
	if (resievedA && resievedB)
	{
		SendOutput(0, true);
	}
	
}
