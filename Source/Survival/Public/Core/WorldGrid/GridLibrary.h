// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridDirectionEnum.h"
#include "IntVector2D.h"
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

	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "ClampDirectionToGrid (Vector)",
			AutoCreateRefTerm = "Direction",
			CompactNodeTitle = "Clamp to grid",
			BlueprintAutocast
		)
	)
	static FVector ClampDirectionToGrid(const FVector& Direction);

	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "ToVector (GridDirection)",
			AutoCreateRefTerm = "Direction",
			CompactNodeTitle = "->",
			BlueprintAutocast
		)
	)
	static FVector GetDirectionFromGridDirection(const EGridDirection Direction);

	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "ToRotation (GridDirection)",
			AutoCreateRefTerm = "Direction",
			CompactNodeTitle = "->",
			BlueprintAutocast
		)
	)
	static FRotator GetRotationFromGridDirection(const EGridDirection Direction);

	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "ToIntVector2D (Vector)",
			AutoCreateRefTerm = "Vector",
			CompactNodeTitle = "->",
			BlueprintAutocast
		)
	)
	static FIntVector2D VectorToIntVector2D(const FVector& Vector);

	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "ToVector (IntVector2D)",
			AutoCreateRefTerm = "Vector",
			CompactNodeTitle = "->",
			BlueprintAutocast
		)
	)
	static FVector IntVector2DToVector(const FIntVector2D& Vector);

	UFUNCTION(
		BlueprintPure,
		Category = "GridLibrary",
		meta = (
			DisplayName = "Inverse (GridDirection)",
			AutoCreateRefTerm = "Direction",
			CompactNodeTitle = "INVERSE",
			BlueprintAutocast
		)
	)
	static EGridDirection InvertGridDirection(const EGridDirection Direction);
};
