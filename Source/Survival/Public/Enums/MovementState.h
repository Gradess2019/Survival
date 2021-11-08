// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MovementState.generated.h"

UENUM(
	BlueprintType,
	Blueprintable
)
enum class EMovementState : uint8
{
	Idle,
	Crouch,
	Walk,
	Run,
	Sprint
};
