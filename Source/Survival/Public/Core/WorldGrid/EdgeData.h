// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdgeData.generated.h"

USTRUCT(BlueprintType)
struct FEdgeData
{
	GENERATED_BODY()

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "EdgeData"
	)
	const UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "EdgeData"
	)
	int32 InstanceId;

	FEdgeData(
		const UInstancedStaticMeshComponent* InstancedStaticMeshComponent = nullptr,
		int32 InstanceId = -1
	)
		: InstancedStaticMeshComponent(InstancedStaticMeshComponent),
		  InstanceId(InstanceId)
	{
	}

	bool operator==(const FEdgeData& Other) const
	{
		return Equals(Other);
	}

	bool Equals(const FEdgeData& Other) const
	{
		return InstancedStaticMeshComponent == Other.InstancedStaticMeshComponent && InstanceId == Other.InstanceId;
	}

	bool IsValid() const
	{
		return InstancedStaticMeshComponent != nullptr && InstanceId >= 0;
	}
};
