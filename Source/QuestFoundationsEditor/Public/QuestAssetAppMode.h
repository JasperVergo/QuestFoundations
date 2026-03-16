#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/** Application mode for main behavior tree editing mode */
class QuestAssetAppMode : public FApplicationMode
{
public:
	QuestAssetAppMode(TSharedPtr<class QuestFoundationsApp> app);

	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

protected:
	TWeakPtr<class QuestFoundationsApp> _app;
	FWorkflowAllowedTabSet _tabs;
};
