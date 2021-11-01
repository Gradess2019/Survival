// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGrid/Grid.h"
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
class SURVIVAL_API AWorldGrid : public AActor, public IGrid
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

	UPROPERTY
	(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "WorldGrid|Debug"
	)
	int32 GridSize;

	UPROPERTY(
		BlueprintReadOnly,
		Category = "WorldGrid|Debug"
	)
	TMap<FIntVector2D, UGridCell*> Cells;

public:
	virtual void BeginPlay() override;

#pragma region IGrid implementation
	virtual UGridCell* CreateCell_Implementation(const FIntVector2D& Key) override;
	virtual UGridCell* GetCellByLocationAndDirection_Implementation(const FVector& Location, EGridDirection Direction, const int32 Id) override;
	virtual FVector GetCellLocation_Implementation(const FVector& Location, EGridDirection Direction, const int32 Id) override;
	virtual FVector SnapLocation_Implementation(const FVector& Vector) override;
	virtual TMap<FIntVector2D, UGridCell*> GetCells_Implementation() const override;
	virtual int32 GetGridSize_Implementation() override;
#pragma endregion IGrid implementation

	UFUNCTION()
	void SpawnTiles(int32 X, int32 Y);

	UFUNCTION(
		BlueprintCallable,
		Category = "WorldGrid|Debug"
	)
	void CreateDebugMeshForCell(const FIntVector2D& Location);
};
