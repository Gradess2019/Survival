// Copyright Gradess. All Rights Reserved.

#include "Core/WorldGrid/GridLibrary.h"
#if WITH_GAMEPLAY_DEBUGGER
#include "Debugger/GridDebuggerCategory.h"

FGridDebuggerCategory::FGridDebuggerCategory()
{
	Direction = EGridDirection::None;
	bShowOnlyWithDebugActor = false;
}

void FGridDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	const auto Pawn = OwnerPC->GetPawn();
	if (!Pawn)
	{
		Direction = EGridDirection::None;
		return;
	}

	Direction = UGridLibrary::GetGridDirectionForActor(Pawn);
}

void FGridDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	const auto DirectionName = UEnum::GetValueAsString(Direction);
	CanvasContext.Printf(TEXT("{white}Direction: {yellow}%s"), *DirectionName);
}

TSharedRef<FGameplayDebuggerCategory> FGridDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FGridDebuggerCategory());
}
#endif
