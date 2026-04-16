#pragma once

#include "CoreMinimal.h"
#include "QuestGraphRuntime.h"
#include "QuestAsset.generated.h"


UCLASS(BlueprintType)
class QUESTFOUNDATIONSRUNTIME_API UQuestAsset : public UObject {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FString QuestName = TEXT("Enter Quest Name Here");

    
    
    UPROPERTY()
    UQuestGraphRuntimeGraph* graph = nullptr;
    
    
};
