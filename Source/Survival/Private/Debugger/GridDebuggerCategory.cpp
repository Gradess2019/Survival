// Copyright Gradess. All Rights Reserved.

#if WITH_GAMEPLAY_DEBUGGER
#include "Debugger/GridDebuggerCategory.h"

FGridDebuggerCategory::FGridDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;
}

void FGridDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);
}

void FGridDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);
}

TSharedRef<FGameplayDebuggerCategory> FGridDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FGridDebuggerCategory());
}
#endif