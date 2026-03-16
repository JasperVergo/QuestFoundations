// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestFoundationsEditor.h"
#include "QuestAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "EdGraphUtilities.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"

#define LOCTEXT_NAMESPACE "FQuestFoundationsEditorModule"

class SQuestGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SQuestGraphPin) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& inArgs) {}
	
	void Construct(const FArguments& inArgs, UEdGraphPin* inGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), inGraphPinObj);
	}
	
protected:
	virtual FSlateColor GetPinColor() const override {return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f));}
};

struct FQuestGraphPinFactory : public FGraphPanelPinFactory
{
public:
	virtual ~FQuestGraphPinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* pin) const override
	{
		if (FName(TEXT("QuestPin")) == pin->PinType.PinSubCategory)
		{
			return SNew(SQuestGraphPin, pin);
		}
		return nullptr;
	}
};

void FQuestFoundationsEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& assetToolsModule = IAssetTools::Get();
	//TODO: this should be in a config file
	EAssetTypeCategories::Type assetType = assetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("QuestFoundations")), LOCTEXT("QuestFoundations", "Quest Foundations"));
	TSharedPtr<QuestAssetAction> customAssetAction = MakeShareable(new QuestAssetAction(assetType));
	assetToolsModule.RegisterAssetTypeActions(customAssetAction.ToSharedRef());
	
	
	//setting the asset icon
	_styleSet = MakeShareable(new FSlateStyleSet(TEXT("QuestFoundationsEditorStyle")));
	TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin("QuestFoundations");
	FString contentDir = plugin->GetContentDir();
	_styleSet->SetContentRoot(contentDir);
	
	//accual thumbnail 
	//TODO: make a better icon for this
	FSlateImageBrush* thrumbnailBrush = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("Icons/QuestIcon"), TEXT(".png")), FVector2D(128.0f, 128.0f));
	FSlateImageBrush* iconBrush = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("Icons/QuestIcon"), TEXT(".png")), FVector2D(128.0f, 128.0f));
	FSlateImageBrush* nodeAddPinIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("Icons/QuestIcon"), TEXT(".png")), FVector2D(128.0f, 128.0f));
	FSlateImageBrush* nodeDeletePinIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("Icons/QuestIcon"), TEXT(".png")), FVector2D(128.0f, 128.0f));
	FSlateImageBrush* nodeDeleteNodeIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("Icons/QuestIcon"), TEXT(".png")), FVector2D(128.0f, 128.0f));
	FSlateImageBrush* nodePinOutputIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("Icons/QuestPinOutputIcon"), TEXT(".png")), FVector2D(128.0f, 128.0f));
	FSlateImageBrush* nodePinInputIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("Icons/QuestPinInputIcon"), TEXT(".png")), FVector2D(128.0f, 128.0f));

	_styleSet->Set(TEXT("ClassThumbnail.QuestAsset"), thrumbnailBrush);
	_styleSet->Set(TEXT("ClassIcon.QuestAsset"), iconBrush);
	_styleSet->Set(TEXT("QuestFoundation.NodeAddPinIcon"), nodeAddPinIcon);
	_styleSet->Set(TEXT("QuestFoundation.NodeDeletePinIcon"), nodeDeletePinIcon);
	_styleSet->Set(TEXT("QuestFoundations.NodeDeleteNodeIcon"), nodeDeleteNodeIcon);
	_styleSet->Set(TEXT("QuestFoundations.NodePinOutput"), nodePinOutputIcon);
	_styleSet->Set(TEXT("QuestFoundations.NodePinInput"), nodePinInputIcon);
	FSlateStyleRegistry::RegisterSlateStyle(*_styleSet.Get());
	
	
	_pinFactory = MakeShareable(new FQuestGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(_pinFactory);
}	

void FQuestFoundationsEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateStyleRegistry::UnRegisterSlateStyle(*_styleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(_pinFactory);

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestFoundationsEditorModule, QuestFoundationsEditor)