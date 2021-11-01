// Copyright Gradess. All Rights Reserved.


#include "Core/WorldGrid/GridLibrary.h"

#include "Core/WorldGrid/IntVector2D.h"
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
	return GetDirectionFromGridDirection(GridDirection);
}

FVector UGridLibrary::GetDirectionFromGridDirection(const EGridDirection Direction)
{
	switch (Direction)
	{
	case EGridDirection::None: return FVector::ZeroVector;
	case EGridDirection::North: return FVector::ForwardVector;
	case EGridDirection::South: return FVector::BackwardVector;
	case EGridDirection::West: return FVector::LeftVector;
	case EGridDirection::East: return FVector::RightVector;
	default: return FVector::ZeroVector;
	}
}

FRotator UGridLibrary::GetRotationFromGridDirection(const EGridDirection Direction)
{
	switch (Direction)
	{
	case EGridDirection::None: return FRotator::ZeroRotator;
	case EGridDirection::North: return FRotator::ZeroRotator;
	case EGridDirection::South: return FRotator(0.f, 180.f, 0.f);
	case EGridDirection::West: return FRotator(0.f, -90.f, 0.f);
	case EGridDirection::East: return FRotator(0.f, 90.f, 0.f);
	default: return FRotator::ZeroRotator;
	}
}

FIntVector2D UGridLibrary::VectorToIntVector2D(const FVector& Vector)
{
	return Vector;
}

FVector UGridLibrary::IntVector2DToVector(const FIntVector2D& Vector)
{
	return Vector;
}
