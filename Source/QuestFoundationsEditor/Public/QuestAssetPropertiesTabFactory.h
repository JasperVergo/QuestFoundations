#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class QuestAssetPropertiesTabFactory : public FWorkflowTabFactory {
public:
	QuestAssetPropertiesTabFactory(TSharedPtr<class QuestFoundationsApp> app);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

protected:
	TWeakPtr<class QuestFoundationsApp> _app;
};
