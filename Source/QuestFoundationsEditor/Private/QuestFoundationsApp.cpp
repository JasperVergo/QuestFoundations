#include "QuestFoundationsApp.h"
#include "QuestAssetAppMode.h"
#include "QuestAsset.h"
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
	
	_graphChangeListenerHandle = _workingGraph->AddOnGraphChangedHandler(
		FOnGraphChanged::FDelegate::CreateSP(this, &QuestFoundationsApp::OnGraphChanged)	
	);
}

void QuestFoundationsApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	_workingGraph->RemoveOnGraphChangedHandler(_graphChangeListenerHandle);
	FAssetEditorToolkit::OnClose();
}

void QuestFoundationsApp::OnGraphChanged(const FEdGraphEditAction& editAction)
{
	UpdateWorkingAssetFromGraph();
}

void QuestFoundationsApp::UpdateWorkingAssetFromGraph()
{
	if (_workingAsset == nullptr && _workingGraph == nullptr)
	{
		return;
	}
	
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
		
		runtimeGraph->Nodes.Add(runtimeNode);
		
	}
	for (std::pair<FGuid, FGuid> connection : connections)
	{
		UQuestGraphRuntimePin* pin1 = idToPinMap[connection.first];
		UQuestGraphRuntimePin* pin2 = idToPinMap[connection.second];
		pin1->connection = pin2;
	}
}

void QuestFoundationsApp::UpdateEditorAssetFromWorkingAsset()
{
	if (_workingAsset->graph == nullptr)
	{
		return;
	}
	
	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UEdGraphPin*> idToPinMap;
	
	for (UQuestGraphRuntimeNode* runtimeNode : _workingAsset->graph->Nodes)
	{
		UQuestStepGraphNode* newNode = NewObject<UQuestStepGraphNode>(_workingGraph);
		newNode->CreateNewGuid();
		newNode->NodePosX = runtimeNode->position.X;
		newNode->NodePosY = runtimeNode->position.Y;
		
		if (runtimeNode->InputPin[0] != nullptr)
		{
			UQuestGraphRuntimePin* pin = runtimeNode->InputPin[0];
			UEdGraphPin* uiPin = newNode->CreateQuestPin(EEdGraphPinDirection::EGPD_Input, pin->pinName);
			uiPin->PinId = pin->pinID;
			
			if (pin->connection != nullptr)
			{
				connections.Add(std::make_pair(pin->pinID, pin->connection->pinID));
			}
			idToPinMap.Add(pin->pinID, uiPin);
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
