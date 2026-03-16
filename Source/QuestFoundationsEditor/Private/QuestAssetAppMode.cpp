#include "QuestAssetAppMode.h"
#include "QuestFoundationsApp.h"
#include "QuestAssetPrimaryTabFactory.h"
#include "QuestAssetPropertiesTabFactory.h"

QuestAssetAppMode::QuestAssetAppMode(TSharedPtr<QuestFoundationsApp> app) : FApplicationMode(TEXT("QuestAssetAppMode")) {
    _app = app;
    _tabs.RegisterFactory(MakeShareable(new QuestAssetPrimaryTabFactory(app)));
	_tabs.RegisterFactory(MakeShareable(new QuestAssetPropertiesTabFactory(app)));

    TabLayout = FTabManager::NewLayout("QuestAssetAppMode_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->Split
					(
							FTabManager::NewStack()
								->SetSizeCoefficient(0.75f)
								->AddTab(FName(TEXT("QuestAssetPrimaryTab")), ETabState::OpenedTab)
					)
					->Split
					(
							FTabManager::NewStack()
								->SetSizeCoefficient(0.25f)
								->AddTab(FName(TEXT("QuestAssetPropertiesTab")), ETabState::OpenedTab)
					)
						
					
			)
	);
}

void QuestAssetAppMode::RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) {
    TSharedPtr<QuestFoundationsApp> app = _app.Pin();
	app->PushTabFactories(_tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void QuestAssetAppMode::PreDeactivateMode() {
	FApplicationMode::PreDeactivateMode();
}

void QuestAssetAppMode::PostActivateMode() {
	FApplicationMode::PostActivateMode();
}
