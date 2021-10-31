// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridDirectionEnum.h"
#include "GameFramework/Actor.h"
#include "GridCell.generated.h"

UCLASS(
	BlueprintType,
	Blueprintable
)
class SURVIVAL_API AGridCell : public AActor
{
	GENERATED_BODY()

public:
	AGridCell();

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

protected:
	UPROPERTY(
		BlueprintGetter = "GetEdgeActors"
	)
	TMap<EGridDirection, AActor*> EdgeActors;
};
