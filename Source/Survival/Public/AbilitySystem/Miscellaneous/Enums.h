// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(
	BlueprintType,
	meta = (
		BitFlags
	)
)
enum class EMovementState : uint8
{
	Idle,
	Walk,
	Run
};
