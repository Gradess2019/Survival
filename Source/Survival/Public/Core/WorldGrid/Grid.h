// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridDirectionEnum.h"
#include "IntVector2D.h"
#include "UObject/Interface.h"
#include "Grid.generated.h"


#pragma region Forward declarations
class UGridCell;
#pragma endregion Forward declarations


UINTERFACE()
class UGrid : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_API IGrid
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Grid",
		meta = (
			AutoCreateRefTerm = "Key"
		)
	)
	UGridCell* CreateCell(const FIntVector2D& Key);

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Grid",
		meta = (
			AutoCreateRefTerm = "Location"
		)
	)
	UGridCell* GetCellByLocationAndDirection(
		const FVector& Location,
		const EGridDirection Direction,
		const int32 Id = 1
	);

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Grid",
		meta = (
			AutoCreateRefTerm = "Location"
		)
	)
	FVector GetCellLocation(
		const FVector& Location,
		const EGridDirection Direction,
		const int32 Id = 1
	);
	
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Grid",
		meta = (
			AutoCreateRefTerm = "Vector"
		)
	)
	FVector SnapLocation(const FVector& Vector);

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Grid"
	)
	TMap<FIntVector2D, UGridCell*> GetCells() const;

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Grid"
	)
	int32 GetGridSize();
};
