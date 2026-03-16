#include "QuestAssetAction.h"
#include "QuestAsset.h"
#include "QuestFoundationsApp.h"

QuestAssetAction::QuestAssetAction(EAssetTypeCategories::Type category) {
    _assetCategory = category;
}

FText QuestAssetAction::GetName() const {
    //TODO: this should not be hard Coded
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_QuestAsset", "Quest");
}

FColor QuestAssetAction::GetTypeColor() const {
    return FColor::Cyan;
}

UClass* QuestAssetAction::GetSupportedClass() const {
    return UQuestAsset::StaticClass();
}

void QuestAssetAction::OpenAssetEditor(const TArray<UObject*>& inObjects, TSharedPtr<class IToolkitHost> editWithinLevelEditor) {
    EToolkitMode::Type mode = editWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* object : inObjects) {
		UQuestAsset* customAsset = Cast<UQuestAsset>(object);
		if (customAsset != nullptr) {
			TSharedRef<QuestFoundationsApp> editor(new QuestFoundationsApp());
			editor->InitEditor(mode, editWithinLevelEditor, customAsset);
		}
	}
}

uint32 QuestAssetAction::GetCategories() {
    return _assetCategory;
}
