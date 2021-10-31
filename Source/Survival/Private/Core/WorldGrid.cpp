// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid.h"


AWorldGrid::AWorldGrid()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CellSize = 100;
	SizeX = 100;
	SizeY = 100;
}

void AWorldGrid::BeginPlay()
{
	Super::BeginPlay();

	if (bDebug)
	{
		SpawnTiles(SizeX, SizeY);
	}
}

void AWorldGrid::SpawnTiles(int32 X, int32 Y)
{
	if (!IsValid(InstancedStaticMeshComponent))
	{
		InstancedStaticMeshComponent = FindComponentByClass<UInstancedStaticMeshComponent>();
		if (!IsValid(InstancedStaticMeshComponent)) { return; }
	}

	const int32 HalfX = X / 2;
	const int32 HalfY = Y / 2;
	for (int32 CurrentY = -HalfY; CurrentY < HalfY; ++CurrentY)
	{
		for (int32 CurrentX = -HalfX; CurrentX < HalfX; ++CurrentX)
		{
			auto InstanceLocation = FVector(CurrentX * CellSize, CurrentY * CellSize, 0.f);
			InstancedStaticMeshComponent->AddInstance(FTransform(InstanceLocation));
		}
	}
}
