#include "QuestFoundationsApp.h"
#include "QuestAssetAppMode.h"
#include "QuestAsset.h"
#include "QuestStep.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "QuestFoundationsGraphSchema.h"
#include "QuestGraphRuntime.h"
#include "QuestStepGraphNode.h"

void QuestFoundationsApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& tabManager) {
    FWorkflowCentricApplication::RegisterTabSpawners(tabManager);
}

void QuestFoundationsApp::InitEditor(
	const EToolkitMode::Type mode, const TSharedPtr<class IToolkitHost>& initToolkitHost, UObject* inObject) {
	TArray<UObject*> objectsToEdit;
    objectsToEdit.Add(inObject);
    
    _workingAsset = Cast<UQuestAsset>(inObject);
	_workingAsset->SetPreSaveListener([this] () { OnWorkingAssetPreSave(); });
	
	_workingGraph = FBlueprintEditorUtils::CreateNewGraph(
		GetWorkingAsset(),
		NAME_None,
		UEdGraph::StaticClass(),
		UQuestFoundationsGraphSchema::StaticClass()
	);

	InitAssetEditor( 
        mode, 
        initToolkitHost, 
        TEXT("QuestFoundations"), 
        FTabManager::FLayout::NullLayout, 
        true, // createDefaultStandaloneMenu 
        true,  // createDefaultToolbar
        objectsToEdit);

    // Add our modes (just one for this example)
    AddApplicationMode(TEXT("QuestFoundationsAppMode"), MakeShareable(new QuestAssetAppMode(SharedThis(this))));

    // Set the mode
    SetCurrentMode(TEXT("QuestFoundationsAppMode"));
	
	UpdateEditorAssetFromWorkingAsset();
	
	
}

void QuestFoundationsApp::setSelectedNodeDetailView(TSharedPtr<class IDetailsView> detailsView)
{
	_selectedNodeDetailView = detailsView;
	_selectedNodeDetailView->OnFinishedChangingProperties().AddRaw(this, &QuestFoundationsApp::OnNodeDetailsViewPropertiesUpdated);
}

void QuestFoundationsApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& selection)
{
	//find first
	for (UObject* obj : selection)
	{
		UQuestStepGraphNode* node = Cast<UQuestStepGraphNode>(obj);
		if (node != nullptr)
		{
			_selectedNodeDetailView->SetObject(node->getNodeClass());
			return;
		}
	}
	_selectedNodeDetailView->SetObject(nullptr);
}

void QuestFoundationsApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	_workingAsset->SetPreSaveListener(nullptr);
	FAssetEditorToolkit::OnClose();
}

void QuestFoundationsApp::OnNodeDetailsViewPropertiesUpdated(const FPropertyChangedEvent& event)
{
	if (_workingGraphUI != nullptr)
	{
		_workingGraphUI->NotifyGraphChanged();
	}
}

void QuestFoundationsApp::OnWorkingAssetPreSave()
{
	UpdateWorkingAssetFromGraph();
}



//is called when saving graph
void QuestFoundationsApp::UpdateWorkingAssetFromGraph()
{
	
	if (_workingAsset == nullptr && _workingGraph == nullptr)
	{
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Saved Quest Graph"));
	
	UQuestGraphRuntimeGraph* runtimeGraph = NewObject<UQuestGraphRuntimeGraph>(_workingAsset);
	_workingAsset->graph = runtimeGraph;
	
	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UQuestGraphRuntimePin*> idToPinMap;
	
	for (UEdGraphNode* uiNode : _workingGraph->Nodes)
	{
		
		UQuestGraphRuntimeNode* runtimeNode = NewObject<UQuestGraphRuntimeNode>(runtimeGraph);
		runtimeNode->position = FVector2D(uiNode->GetPosition().X, uiNode->GetPosition().Y);

		
		for (UEdGraphPin* uiPin : uiNode->Pins)
		{
			UQuestGraphRuntimePin* runtimePin = NewObject<UQuestGraphRuntimePin>(runtimeNode);
			runtimePin->pinName = uiPin->PinName;
			runtimePin->pinID = uiPin->PinId;
			runtimePin->parent = runtimeNode;
			
			if (uiPin->HasAnyConnections() && uiPin->Direction == EGPD_Output)
			{
				std::pair<FGuid, FGuid> connection = std::make_pair(uiPin->PinId, uiPin->LinkedTo[0]->PinId);
				connections.Add(connection);
			}
			
			idToPinMap.Add(uiPin->PinId, runtimePin); 
			if (uiPin->Direction == EGPD_Input)
			{ 
				runtimeNode->InputPin.Add(runtimePin);
			} else
			{
				runtimeNode->OutputPins.Add(runtimePin);
			}
			
		}
		
		UQuestStepGraphNode* uiGraphNode = Cast<UQuestStepGraphNode>(uiNode);  
		runtimeNode->nodeClass = DuplicateObject(uiGraphNode->getNodeClass(), runtimeNode);
		runtimeNode->nodeClass->SetParent(runtimeNode);
		
		runtimeGraph->Nodes.Add(runtimeNode);
		
	}
	for (std::pair<FGuid, FGuid> connection : connections)
	{
		UQuestGraphRuntimePin* pin1 = idToPinMap[connection.first];
		UQuestGraphRuntimePin* pin2 = idToPinMap[connection.second];
		pin1->connection = pin2;
	}
	
}
//is called when loading graph 
void QuestFoundationsApp::UpdateEditorAssetFromWorkingAsset()
{
	
	if (_workingAsset->graph == nullptr)
	{
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Loaded Quest Graph"));
	
	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UEdGraphPin*> idToPinMap;
	
	for (UQuestGraphRuntimeNode* runtimeNode : _workingAsset->graph->Nodes)
	{
		UQuestStepGraphNode* newNode = NewObject<UQuestStepGraphNode>(_workingGraph);
		newNode->CreateNewGuid();
		newNode->NodePosX = runtimeNode->position.X;
		newNode->NodePosY = runtimeNode->position.Y;
		
		if (runtimeNode->nodeClass != nullptr)
		{
			newNode->setNodeClass(DuplicateObject(runtimeNode->nodeClass, runtimeNode));
		}
		else
		{
			newNode->setNodeClass(NewObject<UQuestStep>(runtimeNode));
		}
		
		if (runtimeNode->InputPin.Num() > 0)
		{
			for (UQuestGraphRuntimePin* inPin : runtimeNode->InputPin)
			{
				if (inPin != nullptr)
				{
					UQuestGraphRuntimePin* pin = inPin;
					UEdGraphPin* uiPin = newNode->CreateQuestPin(EEdGraphPinDirection::EGPD_Input, pin->pinName);
					uiPin->PinId = pin->pinID;
			
					if (pin->connection != nullptr)
					{
						connections.Add(std::make_pair(pin->pinID, pin->connection->pinID));
					}
					idToPinMap.Add(pin->pinID, uiPin);
				}
			}
		}
		
		for (UQuestGraphRuntimePin* pin : runtimeNode->OutputPins)
		{
			UEdGraphPin* uiPin = newNode->CreateQuestPin(EEdGraphPinDirection::EGPD_Output, pin->pinName); 
			uiPin->PinId = pin->pinID;
			
			if (pin->connection != nullptr)
			{
				connections.Add(std::make_pair(pin->pinID, pin->connection->pinID));
			}
			idToPinMap.Add(pin->pinID, uiPin);
			
		}
		
		_workingGraph->AddNode(newNode, true, true);
	}
	
	for (std::pair<FGuid, FGuid> connection : connections)
	{
		UEdGraphPin* fromPin = idToPinMap[connection.first];
		UEdGraphPin* toPin = idToPinMap[connection.second];	
		fromPin->LinkedTo.Add(toPin);
		toPin->LinkedTo.Add(fromPin);
	}
	
}
