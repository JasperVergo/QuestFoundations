#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class QuestAssetPrimaryTabFactory : public FWorkflowTabFactory {
public:
	QuestAssetPrimaryTabFactory(TSharedPtr<class QuestFoundationsApp> app);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

protected:
	TWeakPtr<class QuestFoundationsApp> _app;
};
