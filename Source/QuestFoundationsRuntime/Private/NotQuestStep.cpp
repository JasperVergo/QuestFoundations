// Fill out your copyright notice in the Description page of Project Settings.


#include "NotQuestStep.h"

void UNotQuestStep::InitQuestStep()
{
	Super::InitQuestStep();
	
	nodeToolTip = FText::FromString(TEXT("Quests"));
	nodeName = FText::FromString(TEXT("Gate"));
	nodeToolTip = FText::FromString(TEXT("Requires the gate to be open or the continue will fail"));
	inputPins = {"Continue", "Close"};
	outputPins = {"Continue"};
	UE_LOG(LogTemp, Display, TEXT("set up And pin"));
}

void UNotQuestStep::ResievedInput(int inputPinIndex)
{
	Super::ResievedInput(inputPinIndex);
	if (inputPinIndex == 1)
	{
		hasBeenNegated = true;
	}
	else
	{
		if (!hasBeenNegated)
		{
			UE_LOG(LogTemp, Log, TEXT("Passed Through not gate"));
			SendOutput(0);
			
		}
	}
}
