// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestStep.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestStepBegin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStepEnd, UQuestStep*, step);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReievedInput, int, inputPinIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReievedOutput, class UQuestGraphRuntimeNode*, node, int, outputPinIndex);
/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSRUNTIME_API UQuestStep : public UObject
{
	GENERATED_BODY()

	public: //editor interface 
	
	UQuestStep(FText catagory, FText name, FText tooltip, TArray<FName> inPins, TArray<FName> outPins) : 
		inputPins{inPins}, outputPins{outPins}, nodeCatagory{catagory}, nodeName{name}, nodeToolTip{tooltip}
	{}
	
	UQuestStep() {}
	
	virtual ~UQuestStep() = default;
	
	virtual TArray<FName> GetInputPins() {return inputPins;}
	virtual TArray<FName> GetOutputPins() {return outputPins;}
	virtual FText& GetNodeName() {return nodeName;}
	virtual FText& GetNodeToolTip() {return nodeToolTip;}
	virtual FText& GetNodeCategory() {return nodeCatagory;}
	

	
	public: //runtime quest functionallity (override these to make the quest do things
	
	virtual void InitQuestStep() {
		//This is here to be overridden by child classes. this is where you will set the info about your node 
		UE_LOG(LogTemp, Display, TEXT("inited quest step"));
		nodeCatagory = FText::FromString(TEXT("Quests"));
		nodeName = FText::FromString(TEXT("Quest Step"));
		nodeToolTip = FText::FromString(TEXT("Adds a new quest step to the graph"));
		outputPins = {"Input Pin"};
		inputPins = {"Output Pin"};

	}
	
	//don't call these they are for the QuestRunner.h to call 
	virtual void BeginQuestStep();
	virtual void EndQuestStep() {OnQuestStepEnd.Broadcast(this);}
	virtual void TickQuestStep(float DeltaTime) {}
	virtual void ResievedInput(int inputPinIndex) {OnReievedInput.Broadcast(inputPinIndex);}
	void SetParent(class UQuestGraphRuntimeNode* node) {parentNode = node;}
	class UQuestGraphRuntimeNode* getParent() {return parentNode;}
	virtual void setWorldContext(UWorld* Context);
	
	
	//call this in your code to advance the quest 
	virtual void SendOutput(int outputIndex, bool endCurrentNode = true);
	
	public: //Delegetes

	
	UPROPERTY(BlueprintAssignable)
	FOnQuestStepBegin OnQuestStepBegin;
	UPROPERTY(BlueprintAssignable)
	FOnQuestStepEnd OnQuestStepEnd;
	UPROPERTY(BlueprintAssignable)
	FOnReievedInput OnReievedInput;
	UPROPERTY(BlueprintAssignable)
	FOnReievedOutput OnReievedOutput;
	
	//TODO: this should be depricated when deliages are fixed
	class UQuestRunner* owningRunner = nullptr;
	
public:
	UPROPERTY(EditAnywhere)
	FText comments = FText::FromString(TEXT("Comments here"));
	
	protected: //Interface
	
	UPROPERTY()
	bool isRunning;
	
	
	protected: 	//core funtionallity
	
	UPROPERTY()
	UWorld* worldContext = nullptr;
	
	UPROPERTY()	
	TArray<FName> inputPins = {"default Pin"};
	
	UPROPERTY()
	TArray<FName> outputPins = {"default Pin"};
	
	UPROPERTY()
	FText nodeCatagory;
	
	UPROPERTY()
	FText nodeName;
	
	UPROPERTY()
	FText nodeToolTip;
	
	UPROPERTY()
	class UQuestGraphRuntimeNode* parentNode = nullptr;
	

	
	
};
