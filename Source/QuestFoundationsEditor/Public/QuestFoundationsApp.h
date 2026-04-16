#pragma once

#include "CoreMinimal.h"
#include "SGraphPanel.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class QuestFoundationsApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook {
public: // FWorkflowCentricApplication interface
    virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	void InitEditor(const EToolkitMode::Type mode, const TSharedPtr<class IToolkitHost>& initToolkitHost, UObject* inObject);

    class UQuestAsset* GetWorkingAsset() { return _workingAsset; }
	class UEdGraph* GetWorkingGraph() { return _workingGraph; }

	void setWorkingGraphUI(TSharedPtr<SGraphEditor> workingGraphUi) {_workingGraphUI = workingGraphUi;}
	void setSelectedNodeDetailView(TSharedPtr<class IDetailsView> detailsView);	
	void OnGraphSelectionChanged(const FGraphPanelSelectionSet& selection);

	
public: // FAssetEditorToolkit interface
    virtual FName GetToolkitFName() const override { return FName(TEXT("QuestFoundationsEditorApp")); }
    virtual FText GetBaseToolkitName() const override { return FText::FromString(TEXT("QuestFoundationsEditorApp")); }
    virtual FString GetWorldCentricTabPrefix() const override { return TEXT("QuestFoundationsEditorApp"); }
    virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
	//TODO: add github documentation link
	virtual FString GetDocumentationLink() const override { return TEXT(""); }
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override { }
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override { }
	
	virtual void OnClose() override;
	void OnNodeDetailsViewPropertiesUpdated(const FPropertyChangedEvent& event);
	void OnGraphChanged(const FEdGraphEditAction& editAction);

protected:
	void UpdateWorkingAssetFromGraph();
	void UpdateEditorAssetFromWorkingAsset();
	
	
private:
    UPROPERTY()
    class UQuestAsset* _workingAsset = nullptr;
	
	UPROPERTY()
	class UEdGraph* _workingGraph = nullptr;
	
	FDelegateHandle _graphChangeListenerHandle;
	
	//slate widget that displays the graph
	TSharedPtr<SGraphEditor>  _workingGraphUI = nullptr;
	
	TSharedPtr<class IDetailsView> _selectedNodeDetailView = nullptr;
	

};


