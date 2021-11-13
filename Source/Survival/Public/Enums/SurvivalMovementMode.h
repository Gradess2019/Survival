// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalMovementMode.generated.h"

UENUM(
	BlueprintType,
	Blueprintable,
	meta = (
		DisplayName = "EMovementMode"
	)
)
enum class ESurvivalMovementMode : uint8
{
	Idle,
	Crouch,
	Walk,
	Run,
	Sprint
};
