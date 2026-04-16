// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "QuestFoundationsGraphSchema.generated.h"

/**
 * 
 */
UCLASS()
class QUESTFOUNDATIONSEDITOR_API UQuestFoundationsGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	
public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* a, const UEdGraphPin* b) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	
};

USTRUCT()
struct FNewNodeAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()
	
public:
	FNewNodeAction()  {}
	FNewNodeAction(UClass* type, FText inNodeCatigory, FText inMenuDesc, FText inToolTip, const int32 inGrouping) : 
		FEdGraphSchemaAction(inNodeCatigory, inMenuDesc, inToolTip, inGrouping), nodeType(type) {}
	
	virtual UEdGraphNode* PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2D location, bool bSelectNewNode = true) override;
	
private:
	UClass* nodeType;
};
