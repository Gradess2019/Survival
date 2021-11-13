// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridDirectionEnum.h"
#include "GridCell.generated.h"


#pragma region Forward declarations
class AWorldGrid;
#pragma endregion Forward declarations


UCLASS(
	BlueprintType,
	Blueprintable,
	ClassGroup = Survival
)
class SURVIVAL_API UGridCell : public UObject
{
	GENERATED_BODY()

public:
	UGridCell();

protected:
	UPROPERTY(
		SaveGame,
		BlueprintGetter = "GetEdgeStates"
	)
	TMap<EGridDirection, bool> EdgeStates;

public:
	UFUNCTION(
		BlueprintPure,
		Category = "GridCell"
	)
	bool GetEdgeState(EGridDirection Direction);

	UFUNCTION(
		BlueprintCallable,
		Category = "GridCell"
	)
	bool SetEdgeState(
		const EGridDirection Direction,
		const bool bOccupied
	);

	UFUNCTION(
		BlueprintPure,
		BlueprintGetter,
		Category = "GridCell"
	)
	TMap<EGridDirection, bool> GetEdgeStates() const;

#pragma region Debug
protected:
	UPROPERTY(
		BlueprintGetter = "GetMeshId"
	)
	int32 MeshId;

public:
	UFUNCTION(
		BlueprintPure,
		BlueprintGetter,
		Category = "GridCell|Debug"
	)
	int32 GetMeshId() const;
#pragma endregion Debug

	friend AWorldGrid;
};
