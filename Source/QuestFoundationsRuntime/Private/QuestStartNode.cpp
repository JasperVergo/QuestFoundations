// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestStartNode.h"



void UQuestStartNode::InitQuestStep()
{
	//This is here to be overridden by child classes. this is where you will set the info about your node 
	nodeCatagory = FText::FromString(TEXT("Quests"));
	nodeName = FText::FromString(TEXT("Quest Start"));
	nodeToolTip = FText::FromString(TEXT("Adds a new quest start to the graph"));
	outputPins = {"Quest Start"};
	inputPins =  {};
}

void UQuestStartNode::BeginQuestStep()
{
	Super::BeginQuestStep();
}
