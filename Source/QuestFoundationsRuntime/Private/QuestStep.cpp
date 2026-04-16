// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestStep.h"
#include "QuestRunner.h"

DEFINE_LOG_CATEGORY_STATIC(QuestStepSub, Log, All)

void UQuestStep::BeginQuestStep()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Running Node: %s"), *nodeName.ToString()));

	UE_LOG(QuestStepSub, Log, TEXT("Beginning Quest Step %s"), *nodeName.ToString());
	OnQuestStepBegin.Broadcast();
}

void UQuestStep::setWorldContext(UWorld* Context)
{
	if (Context == nullptr)
	{
		UE_LOG(QuestStepSub, Error, TEXT("Context is nullptr in quest step"));
	} else
	{
		UE_LOG(QuestStepSub, Log, TEXT("Context set in quest step"));
	}
	worldContext = Context;
}

void UQuestStep::SendOutput(int outputIndex, bool endCurrentNode)
{
	OnReievedOutput.Broadcast(parentNode, outputIndex); 
	
	//TODO: this needs to be depricated when delegates are fixed
	if (owningRunner)
	{
		owningRunner->AdvanceQuestByIndexWithStop(parentNode, outputIndex, endCurrentNode);
	}
	UE_LOG(QuestStepSub, Log, TEXT("Output connected to %i"), OnReievedOutput.IsBound())
	
	if (endCurrentNode) EndQuestStep();
}
