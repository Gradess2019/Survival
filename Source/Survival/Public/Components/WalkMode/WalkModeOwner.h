// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enums/SurvivalMovementMode.h"
#include "UObject/Interface.h"
#include "WalkModeOwner.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWalkModeOwner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVAL_API IWalkModeOwner
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "WalMode"
	)
	ESurvivalMovementMode GetCurrentMovementMode();

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "WalMode"
	)
	ESurvivalMovementMode GetDefaultMovementMode();

};
