#pragma once

#include "CoreMinimal.h"
#include "QuestGraphRuntime.h"
#include <functional>
#include "QuestAsset.generated.h"


UCLASS(BlueprintType)
class QUESTFOUNDATIONSRUNTIME_API UQuestAsset : public UObject {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FString QuestName = TEXT("Enter Quest Name Here");

public: // Our interface
    void SetPreSaveListener(std::function<void()> onPreSaveListener) { _onPreSaveListener = onPreSaveListener; }

public: // UObject interface
    virtual void PreSave(FObjectPreSaveContext saveContext) override;
    
    UPROPERTY()
    UQuestGraphRuntimeGraph* graph = nullptr;
    
private: // Members
    std::function<void()> _onPreSaveListener = nullptr;

    
};
