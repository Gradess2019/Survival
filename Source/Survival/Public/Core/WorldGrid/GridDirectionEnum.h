// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridDirectionEnum.generated.h"

UENUM(
	BlueprintType,
	Blueprintable
)
enum class EGridDirection : uint8
{
	None,
	North,
	South,
	West,
	East
};
