// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGrid/Grid.h"
#include "WorldGrid/IntVector2D.h"
#include "WorldGrid.generated.h"

#pragma region Log
DECLARE_LOG_CATEGORY_EXTERN(LogWorldGrid, Log, All);
#pragma endregion Log

#pragma region Forward declarations
class UGridCell;
class AWallBuilder;
#pragma endregion Forward declarations

/**
 * @brief Actor that manages creation, deletion, saving, loading grid cells
 */
UCLASS(
	Blueprintable,
	BlueprintType,
	ClassGroup=Survival
)
class SURVIVAL_API AWorldGrid : public AActor, public IGrid
{
	GENERATED_BODY()

public:
	AWorldGrid();

protected:
	/**
	 * @brief Size of 1 cell in unreal units. Size x Size
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		SaveGame,
		Category = "WorldGrid"
	)
	int32 GridSize;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		SaveGame,
		Category = "WorldGrid"
	)
	TSubclassOf<AWallBuilder> WallBuilderClass;

	UPROPERTY(
		BlueprintReadOnly,
		Category = "WorldGrid"
	)
	AWallBuilder* WallBuilder;

	/**
	 * @brief Map of created cells 
	 */
	UPROPERTY(
		BlueprintReadOnly,
		Category = "WorldGrid"
	)
	TMap<FIntVector2D, UGridCell*> Cells;

#pragma region Debug
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
#pragma endregion Debug

public:
	virtual void BeginPlay() override;

#pragma region IGrid implementation
	virtual UGridCell* CreateCell_Implementation(const FIntVector2D& Key) override;

	virtual UGridCell* GetCellByLocationAndDirection_Implementation(
		const FVector& Location,
		EGridDirection Direction,
		const int32 Id
	) override;

	virtual FVector GetCellLocation_Implementation(
		const FVector& Location,
		EGridDirection Direction,
		const int32 Id
	) override;

	virtual FVector SnapLocation_Implementation(const FVector& Vector) override;
	virtual TMap<FIntVector2D, UGridCell*> GetCells_Implementation() const override;
	virtual int32 GetGridSize_Implementation() override;
#pragma endregion IGrid implementation

#pragma region Debug
	UFUNCTION()
	void SpawnTiles(int32 X, int32 Y);

	UFUNCTION(
		BlueprintCallable,
		Category = "WorldGrid|Debug"
	)
	void CreateDebugMeshForCell(const FIntVector2D& Location);

	UFUNCTION(
		BlueprintCallable,
		Category = "WorldGrid|Debug"
	)
	void RebuildGridMeshes();
#pragma endregion Debug

#pragma region Serialization
	UFUNCTION(
		BlueprintCallable,
		Category = "WorldGrid"
	)
	bool Save();

	UFUNCTION(
		BlueprintCallable,
		Category = "WorldGrid"
	)
	bool Load();

	UFUNCTION(
		BlueprintPure,
		Category = "WorldGrid"
	)
	FString GetSaveFilePath() const;
#pragma endregion Serialization

};
