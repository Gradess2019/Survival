// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "GridDirectionEnum.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "WallBuilder.generated.h"


#pragma region Forward declarations
class IGrid;
#pragma endregion Forward declarations


/**
 * @brief Simple wall builder
 */
UCLASS(
	BlueprintType,
	Blueprintable,
	ClassGroup = Survival
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

public:
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
		BlueprintCallable,
		Category = "WallBuilder"
	)
	void LoadWalls(
		const TMap<FIntVector2D, UGridCell*>& Cells
	);

	UFUNCTION(
		BlueprintCallable,
		Category = "WallBuilder"
	)
	bool RemoveWall(const int32 Id);

	UFUNCTION(
		BlueprintCallable,
		Category = "WallBuilder"
	)
	void RemoveWalls();

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

	UFUNCTION(
		BlueprintCallable,
		Category = "WallBuilder"
	)
	void SetGrid(UObject* NewGrid);

protected:
	UFUNCTION()
	int32 CreateMesh(
		EGridDirection Direction,
		FVector CellLocation
	);
};
