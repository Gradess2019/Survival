// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.generated.h"

USTRUCT(BlueprintType)
struct FIntVector2D
{
	GENERATED_BODY()

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "WorldGrid"
	)
	int32 X;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "WorldGrid"
	)
	int32 Y;

	FIntVector2D(const int32 X = 0, const int32 Y = 0) : X(X), Y(Y)
	{
	}

	FIntVector2D(const FVector& Vector): X(Vector.X), Y(Vector.Y)
	{
	}

	operator FVector() const
	{
		return FVector(X, Y, 0.f);
	}
	
	bool operator==(const FIntVector2D& Other) const
	{
		return Equals(Other);
	}

	bool Equals(const FIntVector2D& Other) const
	{
		return X == Other.X && Y == Other.Y;
	}
};

FORCEINLINE uint32 GetTypeHash(const FIntVector2D& Vector)
{
	return FCrc::MemCrc32(&Vector, sizeof(FIntVector2D));
}