// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdgeData.h"
#include "GridDirectionEnum.h"
#include "GameFramework/Actor.h"
#include "GridCell.generated.h"

#pragma region Forward declarations
class AWorldGrid;
#pragma endregion Forward declarations


UCLASS(
	BlueprintType,
	Blueprintable
)
class SURVIVAL_API UGridCell : public UObject
{
	GENERATED_BODY()

public:
	UGridCell();

protected:
	UPROPERTY(
		BlueprintGetter = "GetEdgeActors"
	)
	TMap<EGridDirection, FEdgeData> EdgeActors;

	UPROPERTY(
		BlueprintGetter = "GetMeshId"
	)
	int32 MeshId;

public:
	UFUNCTION(
		BlueprintPure,
		Category = "GridCell"
	)
	FEdgeData GetEdgeActor(EGridDirection Direction);

	UFUNCTION(
		BlueprintCallable,
		Category = "GridCell"
	)
	bool SetEdgeInstance(
		const EGridDirection Direction,
		const UInstancedStaticMeshComponent* Mesh,
		const int32 InstanceId
	);

	UFUNCTION(
		BlueprintPure,
		BlueprintGetter,
		Category = "GridCell"
	)
	TMap<EGridDirection, FEdgeData> GetEdgeActors() const;

	UFUNCTION(
		BlueprintPure,
		BlueprintGetter,
		Category = "GridCell"
	)
	int32 GetMeshId() const;

	friend AWorldGrid;
};
