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
