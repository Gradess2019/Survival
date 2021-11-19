// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LineOfSightComponent.generated.h"


#pragma region Log
DECLARE_LOG_CATEGORY_EXTERN(LogLineOfSight, Log, All);
#pragma endregion Log


UCLASS(
	Blueprintable,
	BlueprintType,
	ClassGroup = Survival,
	meta = (
		BlueprintSpawnableComponent
	)
)
class SURVIVAL_API ULineOfSightComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	ULineOfSightComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	FHitResult LaunchTrace(
		const FVector& Start,
		const FVector& End,
		const bool bForceDraw = false
	) const;

	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	void LaunchTraces(UPARAM(DisplayName = "Hits") TArray<FHitResult>& OutHits);
	
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	void PreciseHits(UPARAM(DisplayName = "Hits") TArray<FHitResult>& OutHits);

	UFUNCTION()
	void PreciseHitsByBisectionMethod(
		FHitResult& LeftHit,
		FHitResult& RightHit
	) const;

	UFUNCTION(
		BlueprintPure,
		Category = "LineOfSight"
	)
	bool IsAngleLessThanPreciseAngle(
		const FVector& LeftDirection,
		const FVector& RightDirection
	) const;

	UFUNCTION(
		BlueprintPure,
		Category = "LineOfSight"
	)
	bool IsAnyDistanceEquals(
		float FirstDistanceToX,
		float FirstDistanceToY,
		float SecondDistanceToX,
		float SecondDistanceToY
	) const;

	UFUNCTION(
		BlueprintPure,
		Category = "LineOfSight"
	)
	bool IsAnyHitDistanceEquals(
		const FHitResult& FirstHit,
		const FHitResult& SecondHit
	) const;

	UFUNCTION(
		BlueprintGetter,
		Category = "LineOfSight"
	)
	const TArray<FHitResult>& GetBaseHits() const;

	UFUNCTION(
		BlueprintGetter,
		Category = "LineOfSight"
	)
	const TArray<FHitResult>& GetPrecisedHits() const;

protected:
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	int32 TraceNumber;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	int32 PreciseCount;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float PreciseAngle;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float Angle;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float ErrorTolerance;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float Distance;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	UTextureRenderTarget2D* SightTexture;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	UMaterialParameterCollection* SightParams;

	UPROPERTY(
		BlueprintGetter = GetBaseHits,
		Category = "LineOfSight"
	)
	TArray<FHitResult> BaseHits;

	UPROPERTY(
		BlueprintGetter = GetPrecisedHits,
		Category = "LineOfSight"
	)
	TArray<FHitResult> PrecisedHits;

#pragma region Debug
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight|Debug"
	)
	bool bMeasureTime;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight|Debug"
	)
	TEnumAsByte<ETraceTypeQuery> QueryType;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight|Debug"
	)
	TEnumAsByte<EDrawDebugTrace::Type> DebugType;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight|Debug"
	)
	float DrawTime;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight|Debug"
	)
	FLinearColor TraceColor;

	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight|Debug"
	)
	FLinearColor TraceHitColor;
#pragma endregion Debug

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateSightParams();

	UFUNCTION(BlueprintCallable)
	void DrawHits(UPARAM(ref) TArray<FHitResult>& Hits);

	UFUNCTION()
	FVector GetEndPoint(const FHitResult& Hit) const;

	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	float GetDistanceToAxis(const FVector& Axis, const FVector& Location) const;

	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	float GetDistanceToX(const FVector& Location) const;

	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	float GetDistanceToY(const FVector& Location) const;
};
