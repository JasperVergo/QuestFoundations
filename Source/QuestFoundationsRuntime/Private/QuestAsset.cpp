#include "QuestAsset.h"
#include "UObject/ObjectSaveContext.h"

void UQuestAsset::PreSave(FObjectPreSaveContext saveContext) { 
	//Super::PreSave(saveContext);
	if (_onPreSaveListener) {
		_onPreSaveListener();
	}
}