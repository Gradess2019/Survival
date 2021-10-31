// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridDirectionEnum.h"
#include "UObject/Object.h"
#include "GridLibrary.generated.h"

UCLASS()
class SURVIVAL_API UGridLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "ToGridDirection (Vector)",
			AutoCreateRefTerm = "WorldDirection",
			CompactNodeTitle = "->",
			BlueprintAutocast
		)
	)
	static EGridDirection GetGridDirection(const FVector& WorldDirection);

	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "ToGridDirection (Actor)",
			AutoCreateRefTerm = "WorldDirection",
			CompactNodeTitle = "->",
			BlueprintAutocast
		)
	)
	static EGridDirection GetGridDirectionForActor(AActor* ActorToUse);
};
