// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	TMap<EGridDirection, AActor*> EdgeActors;

	UPROPERTY(
		BlueprintGetter = "GetMeshId"
	)
	int32 MeshId;

public:
	UFUNCTION(
		BlueprintPure,
		Category = "GridCell"
	)
	AActor* GetEdgeActor(EGridDirection Direction);

	UFUNCTION(
		BlueprintCallable,
		Category = "GridCell"
	)
	bool SetEdgeActor(AActor* NewActor, EGridDirection Direction);

	UFUNCTION(
		BlueprintPure,
		BlueprintGetter,
		Category = "GridCell"
	)
	TMap<EGridDirection, AActor*> GetEdgeActors() const;

	UFUNCTION(
		BlueprintPure,
		BlueprintGetter,
		Category = "GridCell"
	)
	int32 GetMeshId() const;

	friend AWorldGrid;
};
