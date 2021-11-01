// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid/GridCell.h"


UGridCell::UGridCell()
{
}

AActor* UGridCell::GetEdgeActor(EGridDirection Direction)
{
	const auto FoundActor = EdgeActors.Find(Direction);
	return FoundActor != nullptr ? *FoundActor : nullptr;
}

bool UGridCell::SetEdgeActor(AActor* NewActor, EGridDirection Direction)
{
	return IsValid(EdgeActors.Add(Direction, NewActor));
}

TMap<EGridDirection, AActor*> UGridCell::GetEdgeActors() const
{
	return EdgeActors;
}

int32 UGridCell::GetMeshId() const
{
	return MeshId;
}

