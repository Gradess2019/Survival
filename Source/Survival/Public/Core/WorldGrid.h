// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGrid.generated.h"

UCLASS(
	Blueprintable,
	BlueprintType
)
class SURVIVAL_API AWorldGrid : public AActor
{
	GENERATED_BODY()

public:
	AWorldGrid();

	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnTiles(int32 X, int32 Y);

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

};
