// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid.h"

#include "Core/WorldGrid/GridCell.h"
#include "Core/WorldGrid/IntVector2D.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(LogWorldGrid);
#define LOG(Format, ...) UE_LOG(LogWorldGrid, Log, TEXT(Format), ##__VA_ARGS__)
#define WARN(Format, ...) UE_LOG(LogWorldGrid, Warning, TEXT(Format), ##__VA_ARGS__)
#define ERROR(Format, ...) UE_LOG(LogWorldGrid, Error, TEXT(Format), ##__VA_ARGS__)

AWorldGrid::AWorldGrid()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GridSize = 100;
	bDebug = false;
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

#pragma region IGrid implementation
UGridCell* AWorldGrid::CreateCell_Implementation(const FIntVector2D& Key)
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

UGridCell* AWorldGrid::GetCellByLocationAndDirection_Implementation(
	const FVector& Location,
	const EGridDirection Direction,
	const int32 Id
)
{
	const auto CellLocation = GetCellLocation_Implementation(Location, Direction, Id);
	return CreateCell_Implementation(CellLocation);
}

FVector AWorldGrid::GetCellLocation_Implementation(
	const FVector& Location,
	const EGridDirection Direction,
	const int32 Id
)
{
	const auto SnapLocation = SnapLocation_Implementation(Location);
	switch (Direction)
	{
	case EGridDirection::North: return SnapLocation + FVector(GridSize * Id, 0, 0);
	case EGridDirection::South: return SnapLocation + FVector(-GridSize * Id, 0, 0);
	case EGridDirection::West: return SnapLocation + FVector(0, -GridSize * Id, 0);
	case EGridDirection::East: return SnapLocation + FVector(0, GridSize * Id, 0);
	default: return FVector::ZeroVector;
	}
}

FVector AWorldGrid::SnapLocation_Implementation(const FVector& Vector)
{
	return UKismetMathLibrary::Vector_SnappedToGrid(Vector, GridSize);
}

TMap<FIntVector2D, UGridCell*> AWorldGrid::GetCells_Implementation() const
{
	return Cells;
}

int32 AWorldGrid::GetGridSize_Implementation()
{
	return GridSize;
}
#pragma endregion IGrid implementation

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
			CreateCell(FIntVector2D(CurrentX * GridSize, CurrentY * GridSize));
		}
	}
}

void AWorldGrid::CreateDebugMeshForCell(const FIntVector2D& Location)
{
	const auto CellPtr = Cells.Find(Location);
	if (!CellPtr) { return; }

	const auto Id = InstancedStaticMeshComponent->AddInstance(FTransform(Location));

	const auto Cell = *CellPtr;
	Cell->MeshId = Id;
}
