// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid.h"

#include "Core/WorldGrid/GridCell.h"
#include "Core/WorldGrid/IntVector2D.h"

DEFINE_LOG_CATEGORY(LogWorldGrid);
#define LOG(Format, ...) UE_LOG(LogWorldGrid, Log, TEXT(Format), ##__VA_ARGS__)
#define WARN(Format, ...) UE_LOG(LogWorldGrid, Warning, TEXT(Format), ##__VA_ARGS__)
#define ERROR(Format, ...) UE_LOG(LogWorldGrid, Error, TEXT(Format), ##__VA_ARGS__)

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
			CreateCell(FIntVector2D(CurrentX * CellSize, CurrentY * CellSize));
		}
	}
}

UGridCell* AWorldGrid::CreateCell(const FIntVector2D& Key)
{
	const auto NewCellPtr = Cells.Find(Key);
	if (NewCellPtr) { return *NewCellPtr; }

	const auto NewCell = NewObject<UGridCell>();
	Cells.Add(Key, NewCell);

	if (bDebug)
	{
		CreateDebugMeshForCell(Key);
	}

	return NewCell;
}

void AWorldGrid::CreateDebugMeshForCell(const FIntVector2D& Location)
{
	const auto CellPtr = Cells.Find(Location);
	if (!CellPtr) { return; }

	const auto Id = InstancedStaticMeshComponent->AddInstance(FTransform(Location));

	const auto Cell = *CellPtr;
	Cell->MeshId = Id;
}

TMap<FIntVector2D, UGridCell*> AWorldGrid::GetCells() const
{
	return Cells;
}
