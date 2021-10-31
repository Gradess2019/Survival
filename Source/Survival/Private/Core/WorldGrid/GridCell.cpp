// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid/GridCell.h"


AGridCell::AGridCell()
{
	PrimaryActorTick.bCanEverTick = true;
}

AActor* AGridCell::GetEdgeActor(EGridDirection Direction)
{
	const auto FoundActor = EdgeActors.Find(Direction);
	return FoundActor != nullptr ? *FoundActor : nullptr;
}

bool AGridCell::SetEdgeActor(AActor* NewActor, EGridDirection Direction)
{
	return IsValid(EdgeActors.Add(Direction, NewActor));
}

TMap<EGridDirection, AActor*> AGridCell::GetEdgeActors() const
{
	return EdgeActors;
}

