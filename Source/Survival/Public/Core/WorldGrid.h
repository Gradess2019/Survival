// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGrid/IntVector2D.h"
#include "WorldGrid.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWorldGrid, Log, All);

#pragma region Forward declarations
class UGridCell;
#pragma endregion Forward declarations

UCLASS(
	Blueprintable,
	BlueprintType
)
class SURVIVAL_API AWorldGrid : public AActor
{
	GENERATED_BODY()

public:
	AWorldGrid();

protected:
#pragma region DebugProperties
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "WorldGrid|Debug"
	)
	bool bDebug;

	UPROPERTY
	(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "WorldGrid|Debug"
	)
	int32 CellSize;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "WorldGrid|Debug"
	)
	int32 SizeX;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "WorldGrid|Debug"
	)
	int32 SizeY;

	UPROPERTY()
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;
#pragma endregion DebugProperties

	UPROPERTY(
		BlueprintGetter = "GetCells",
		Category = "WorldGrid|Debug"
	)
	TMap<FIntVector2D, UGridCell*> Cells;

public:
	virtual void BeginPlay() override;
	void CreateDebugMeshForCell(const FIntVector2D& Location);

	UFUNCTION()
	void SpawnTiles(int32 X, int32 Y);

	UFUNCTION(
		BlueprintGetter,
		Category = "WorldGrid"
	)
	TMap<FIntVector2D, UGridCell*> GetCells() const;

	UFUNCTION(
		BlueprintCallable,
		Category = "WorldGrid",
		meta = (
			AutoCreateRefTerm = "Key"
		)
	)
	UGridCell* CreateCell(const FIntVector2D& Key);

};
