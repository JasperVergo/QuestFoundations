// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceNodeStep.h"

void USequenceNodeStep::InitQuestStep()
{
	Super::InitQuestStep();
	nodeToolTip = FText::FromString(TEXT("Quests"));
	nodeName = FText::FromString(TEXT("Sequence"));
	nodeToolTip = FText::FromString(TEXT("done each of its outputs"));
	inputPins = {"start"};
	outputPins = {"Ouput01", "Output02", "Output03"};
	UE_LOG(LogTemp, Display, TEXT("set up And pin"));
}

void USequenceNodeStep::BeginQuestStep()
{
	Super::BeginQuestStep();
	/*
	for (int i = 0; i < inputPins.Num() - 1; i++)
	{
		SendOutput(i, false);
	}
	*/
	SendOutput(0, false);
	SendOutput(1, false);
	SendOutput(2);

	//SendOutput(inputPins.Num() - 1, true);
}
