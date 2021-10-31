// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid/GridLibrary.h"

#include "Kismet/KismetMathLibrary.h"

EGridDirection UGridLibrary::GetGridDirection(const FVector& WorldDirection)
{
	const auto Yaw = UKismetMathLibrary::Conv_VectorToRotator(WorldDirection).Yaw;

	if (-45.f < Yaw && Yaw <= 45.f)
	{
		return EGridDirection::North;
	}

	if (45.f < Yaw && Yaw <= 135.f)
	{
		return EGridDirection::East;
	}

	if (135.f < Yaw || Yaw <= -135.f)
	{
		return EGridDirection::South;
	}

	return EGridDirection::West;
}

EGridDirection UGridLibrary::GetGridDirectionForActor(AActor* ActorToUse)
{
	if (!IsValid(ActorToUse)) { return EGridDirection::North; }

	return GetGridDirection(ActorToUse->GetActorForwardVector());
}

FVector UGridLibrary::ClampDirectionToGrid(const FVector& Direction)
{
	const auto GridDirection = GetGridDirection(Direction);
	switch (GridDirection)
	{
	case EGridDirection::None: return FVector::ZeroVector;
	case EGridDirection::North: return FVector::ForwardVector;
	case EGridDirection::South: return FVector::BackwardVector;
	case EGridDirection::West: return FVector::LeftVector;
	case EGridDirection::East: return FVector::RightVector;
	default: return FVector::ZeroVector;
	}
}
