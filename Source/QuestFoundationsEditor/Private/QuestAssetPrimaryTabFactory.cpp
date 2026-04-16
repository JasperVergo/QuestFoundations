#include "QuestAssetPrimaryTabFactory.h"
#include "QuestFoundationsApp.h"
#include "QuestAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

QuestAssetPrimaryTabFactory::QuestAssetPrimaryTabFactory(TSharedPtr<QuestFoundationsApp> app) : FWorkflowTabFactory(FName("QuestAssetPrimaryTab"), app) {
    _app = app;
    TabLabel = FText::FromString(TEXT("Primary"));
	ViewMenuDescription = FText::FromString(TEXT("Displays a primary view for whatever you want to do."));
	ViewMenuTooltip = FText::FromString(TEXT("Show the primary view."));
}

TSharedRef<SWidget> QuestAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const {
    TSharedPtr<QuestFoundationsApp> app = _app.Pin();

    SGraphEditor::FGraphEditorEvents graphEvents;
    graphEvents.OnSelectionChanged.BindRaw(app.Get(), &QuestFoundationsApp::OnGraphSelectionChanged);
    
    TSharedPtr<SGraphEditor> GraphEditor = 
        SNew(SGraphEditor)
        .IsEnabled(true)
        .GraphEvents(graphEvents)
        .GraphToEdit(app->GetWorkingGraph());
    app->setWorkingGraphUI(GraphEditor);
    
    return SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .FillHeight(1.0f)
                .HAlign(HAlign_Fill)
                [
                    GraphEditor.ToSharedRef()
                ];
}

FText QuestAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const {
    return FText::FromString(TEXT("A primary view for doing primary things."));
}
