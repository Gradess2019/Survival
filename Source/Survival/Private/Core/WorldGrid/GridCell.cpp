// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid/GridCell.h"


UGridCell::UGridCell()
{
}

FEdgeData UGridCell::GetEdgeActor(EGridDirection Direction)
{
	const auto FoundActor = EdgeActors.Find(Direction);
	return FoundActor != nullptr ? *FoundActor : FEdgeData();
}

bool UGridCell::SetEdgeInstance(
	const EGridDirection Direction,
	const UInstancedStaticMeshComponent* Mesh,
	const int32 InstanceId
	)
{
	return EdgeActors.Add(Direction, FEdgeData(Mesh, InstanceId)).IsValid();
}

TMap<EGridDirection, FEdgeData> UGridCell::GetEdgeActors() const
{
	return EdgeActors;
}

int32 UGridCell::GetMeshId() const
{
	return MeshId;
}

