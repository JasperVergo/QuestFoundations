#include "QuestAssetPropertiesTabFactory.h"
#include "QuestFoundationsApp.h"
#include "QuestAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "QuestStep.h"

QuestAssetPropertiesTabFactory::QuestAssetPropertiesTabFactory(TSharedPtr<QuestFoundationsApp> app) : FWorkflowTabFactory(FName("QuestAssetPropertiesTab"), app) {
	_app = app;
	TabLabel = FText::FromString(TEXT("Details"));
	ViewMenuDescription = FText::FromString(TEXT("Displays the proporties for the selected node."));
	ViewMenuTooltip = FText::FromString(TEXT("Show the show node details."));
}

TSharedRef<SWidget> QuestAssetPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const {
	TSharedPtr<QuestFoundationsApp> app = _app.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	
	
	FDetailsViewArgs detailsViewArgs;
	{
		detailsViewArgs.bAllowSearch = false;
		detailsViewArgs.bHideSelectionTip = true;
		detailsViewArgs.bLockable = false;
		detailsViewArgs.bSearchInitialKeyFocus = true;
		detailsViewArgs.bUpdatesFromSelection = false;
		detailsViewArgs.NotifyHook = nullptr;
		detailsViewArgs.bShowOptions = true;
		detailsViewArgs.bShowModifiedPropertiesOption = false;
		detailsViewArgs.bShowScrollBar = false;
	}

	TSharedPtr<IDetailsView> detailsView = PropertyEditorModule.CreateDetailView(detailsViewArgs);
	detailsView->SetObject(app->GetWorkingAsset());
	
	TSharedPtr<IDetailsView> selectedNodeDetailsView = PropertyEditorModule.CreateDetailView(detailsViewArgs);
	selectedNodeDetailsView->SetObject(nullptr);
	app->setSelectedNodeDetailView(selectedNodeDetailsView);

	return SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.HAlign(HAlign_Fill)
				[
					detailsView.ToSharedRef()
				]				
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.HAlign(HAlign_Fill)
				[
					selectedNodeDetailsView.ToSharedRef()
				];
}

FText QuestAssetPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const {
	return ViewMenuDescription;
}
