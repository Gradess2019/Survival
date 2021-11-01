// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridDirectionEnum.h"
#include "GameFramework/Actor.h"
#include "WallBuilder.generated.h"

#pragma region Forward declarations
class IGrid;
#pragma endregion Forward declarations


UCLASS(
	BlueprintType,
	Blueprintable
)
class SURVIVAL_API AWallBuilder : public AActor
{
	GENERATED_BODY()

public:
	AWallBuilder();

protected:
	UPROPERTY(
		BlueprintReadOnly,
		EditDefaultsOnly,
		Category = "WallBuilder"
	)
	UInstancedStaticMeshComponent* MeshComponent;

	UPROPERTY(
		BlueprintReadOnly,
		Category = "WallBuilder"
	)
	UObject* Grid;

	UFUNCTION(
		BlueprintCallable,
		Category = "WallBuilder",
		meta = (
			AutoCreateRefTerm = "Location"
		)
	)
	int32 CreateWall(
		const FVector& Location,
		const EGridDirection Direction
	);

	UFUNCTION(
		BlueprintPure,
		Category = "WallBuilder"
	)
	UObject* GetWorldGrid() const;

	UFUNCTION(
		BlueprintPure,
		Category = "WallBuilder"
	)
	FVector GetWallOffset(EGridDirection Direction) const;

	UFUNCTION(
		BlueprintPure,
		Category = "WallBuilder"
	)
	FRotator GetWallRotation(EGridDirection Direction) const;

public:
	UFUNCTION(
		BlueprintCallable,
		Category = "WallBuilder"
	)
	void SetGrid(UObject* NewGrid);
};
