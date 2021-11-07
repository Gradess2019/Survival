// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid/GridCell.h"


UGridCell::UGridCell()
{
}

bool UGridCell::GetEdgeState(EGridDirection Direction)
{
	const auto FoundActor = EdgeStates.Find(Direction);
	return FoundActor != nullptr ? *FoundActor : false;
}

bool UGridCell::SetEdgeState(
	const EGridDirection Direction,
	const bool bOccupied
)
{
	return EdgeStates.Add(Direction, bOccupied);
}

TMap<EGridDirection, bool> UGridCell::GetEdgeStates() const
{
	return EdgeStates;
}

int32 UGridCell::GetMeshId() const
{
	return MeshId;
}
