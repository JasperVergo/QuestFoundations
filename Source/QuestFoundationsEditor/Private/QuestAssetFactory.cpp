#include "QuestAssetFactory.h"
#include "QuestAsset.h"

UQuestAssetFactory::UQuestAssetFactory(const FObjectInitializer& objectInitializer) : Super(objectInitializer) {
	SupportedClass = UQuestAsset::StaticClass();
}

UObject* UQuestAssetFactory::FactoryCreateNew(
	UClass* uclass, UObject* inParent, FName name, EObjectFlags flags, UObject* context, FFeedbackContext* warn) {
    UQuestAsset* asset = NewObject<UQuestAsset>(inParent, name, flags);
	return asset;
}

bool UQuestAssetFactory::CanCreateNew() const {
    return true;
}
