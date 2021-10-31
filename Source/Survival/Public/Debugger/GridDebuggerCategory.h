// Copyright Gradess. All Rights Reserved.

#pragma once

#if WITH_GAMEPLAY_DEBUGGER
#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class SURVIVAL_API FGridDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	FGridDebuggerCategory();
	
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
};
#endif