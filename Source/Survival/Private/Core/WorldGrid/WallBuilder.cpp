// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid/WallBuilder.h"

#include "Core/WorldGrid/Grid.h"
#include "Core/WorldGrid/GridCell.h"
#include "Core/WorldGrid/GridLibrary.h"


AWallBuilder::AWallBuilder()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("InstancedStaticMesh");
	MeshComponent->SetupAttachment(RootComponent);
}

int32 AWallBuilder::CreateWall(
	const FVector& Location,
	const EGridDirection Direction
)
{
	const auto CellLocation = IGrid::Execute_SnapLocation(Grid, Location);
	const auto NextCellLocation = IGrid::Execute_GetCellLocation(Grid, Location, Direction, 1);

	const auto WallLocation = CellLocation + GetWallOffset(Direction);
	const auto WallRotation = GetWallRotation(Direction);

	const auto Id = MeshComponent->AddInstanceWorldSpace(FTransform(WallRotation, WallLocation));

	const auto CurrentCell = IGrid::Execute_CreateCell(Grid, CellLocation);
	const auto NextCell = IGrid::Execute_CreateCell(Grid, NextCellLocation);

	const auto InversedDirection = UGridLibrary::InvertGridDirection(Direction);

	CurrentCell->SetEdgeInstance(Direction, MeshComponent, Id);
	NextCell->SetEdgeInstance(InversedDirection, MeshComponent, Id);
	return Id;
}

UObject* AWallBuilder::GetWorldGrid() const
{
	return Cast<UObject>(Grid);
}

FVector AWallBuilder::GetWallOffset(EGridDirection Direction) const
{
	const auto GridSize = IGrid::Execute_GetGridSize(Grid);
	const auto HalfGridSize = GridSize / 2;
	switch (Direction)
	{
	case EGridDirection::North: return FVector(HalfGridSize, -HalfGridSize, 0);
	case EGridDirection::South:
	case EGridDirection::West: return FVector(-HalfGridSize, -HalfGridSize, 0);
	case EGridDirection::East: return FVector(-HalfGridSize, HalfGridSize, 0);
	default: return FVector::ZeroVector;
	}
}

FRotator AWallBuilder::GetWallRotation(EGridDirection Direction) const
{
	switch (Direction)
	{
	case EGridDirection::North: return FRotator(0, 90, 0);
	case EGridDirection::South: return FRotator(0, 90, 0);
	default: return FRotator::ZeroRotator;
	}
}

void AWallBuilder::SetGrid(UObject* NewGrid)
{
	check(NewGrid && NewGrid->Implements<UGrid>())
	Grid = NewGrid;
}
