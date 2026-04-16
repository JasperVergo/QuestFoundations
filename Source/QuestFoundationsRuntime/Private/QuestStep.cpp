// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestStep.h"

DEFINE_LOG_CATEGORY_STATIC(QuestStepSub, Log, All)

void UQuestStep::BeginQuestStep()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Example text that prints a float: %s"), *nodeName.ToString()));

	UE_LOG(QuestStepSub, Log, TEXT("Beginning Quest Step %s"), *nodeName.ToString());
	OnQuestStepBegin.Broadcast();
}

void UQuestStep::SendOutput(int outputIndex, bool endCurrentNode)
{
	OnReievedOutput.Broadcast(outputIndex); 
	if (endCurrentNode) EndQuestStep();
}
