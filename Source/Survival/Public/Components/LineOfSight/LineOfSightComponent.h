// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LineOfSightComponent.generated.h"


#pragma region Log
DECLARE_LOG_CATEGORY_EXTERN(LogLineOfSight, Log, All);
#pragma endregion Log


/**
 * @brief The component that calculates line of sight using line traces and bisection method
 * Result outputs to render texture
 */
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

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	/**
	 * @brief Launch single line trace
	 * @param Start Line trace start
	 * @param End Line trace end
	 * @param bForceDraw Whether draw trace or not
	 * @return Hit result
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	FHitResult LaunchTrace(
		const FVector& Start,
		const FVector& End,
		const bool bForceDraw = false
	) const;

	/**
	 * @brief Launches traces along the angle and caches result to BaseHits
	 * @param OutHits Array of hit results
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	void LaunchTraces(UPARAM(DisplayName = "Hits") TArray<FHitResult>& OutHits);
	
	/**
	 * @brief Make array of more accurate hits and caches result to PrecisedHits
	 * @param OutHits Array of precised hits
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	void PreciseHits(UPARAM(DisplayName = "Hits") TArray<FHitResult>& OutHits);

	/**
	 * @brief Precise left and right hits using bisection method
	 * @param LeftHit Left hit to use
	 * @param RightHit Right hit to use
	 */
	UFUNCTION()
	void PreciseHitsByBisectionMethod(
		FHitResult& LeftHit,
		FHitResult& RightHit
	) const;

	/**
	 * @brief Checks whether angle between left direction and right direction are less than precise angle or not
	 * @param LeftDirection Left direction to use
	 * @param RightDirection Right direction to use
	 * @return true if angle is less
	 */
	UFUNCTION(
		BlueprintPure,
		Category = "LineOfSight"
	)
	bool IsAngleLessThanPreciseAngle(
		const FVector& LeftDirection,
		const FVector& RightDirection
	) const;

	/**
	 * @brief Compares distances to X and Y axes
	 * @param X1 First distance to X axis
	 * @param Y1 First distance to Y axis
	 * @param X2 Second distance to X axis
	 * @param Y2 Second distance to Y axis
	 * @return true if X1 == X2 or Y1 == Y2
	 */
	UFUNCTION(
		BlueprintPure,
		Category = "LineOfSight"
	)
	bool IsAnyDistanceEquals(
		float X1,
		float Y1,
		float X2,
		float Y2
	) const;

	/**
	 * @brief Compares distances to X and Y axes
	 * @see IsAnyDistanceEquals()
	 * @param FirstHit First hit to use
	 * @param SecondHit Second hit to use
	 * @return true if X1 == X2 or Y1 == Y2
	 */
	UFUNCTION(
		BlueprintPure,
		Category = "LineOfSight"
	)
	bool IsAnyHitDistanceEquals(
		const FHitResult& FirstHit,
		const FHitResult& SecondHit
	) const;

	/**
	 * @brief Cached result of LaunchTraces()
	 * @see LaunchTraces()
	 * @return Array of NOT precised hits
	 */
	UFUNCTION(
		BlueprintGetter,
		Category = "LineOfSight"
	)
	const TArray<FHitResult>& GetBaseHits() const;

	/**
	 * @brief Cached result of PreciseHits()
	 * @see PreciseHits()
	 * @return Array of precised hits
	 */
	UFUNCTION(
		BlueprintGetter,
		Category = "LineOfSight"
	)
	const TArray<FHitResult>& GetPrecisedHits() const;

protected:
	/**
	 * @brief Number of traces. The higher number, the higher CPU consumption, but the better precision
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	int32 TraceNumber;

	/**
	 * @brief Limit for bisection method iterations. The higher number, the higher CPU consumption, but the better precision
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	int32 PreciseCount;

	/**
	 * @brief Target minimal appropriate angle for bisection method result. The lesser number, the higher CPU consumption, but the better precision
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float PreciseAngle;

	/**
	 * @brief Line of sight angle. Basically, it is like FOV
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float Angle;

	/**
	 * @brief Error tolerance for comparing distance to axes
	 * @see IsAnyDistanceEquals()
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float ErrorTolerance;

	/**
	 * @brief How far actor can see. Basically, it is just trace length
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	float Distance;

	/**
	 * @brief 2D Render texture to draw calculated precised hits
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	UTextureRenderTarget2D* SightTexture;

	/**
	 * @brief Sight material params
	 * It must has contain PlayerLocation and Size params
	 */
	UPROPERTY(
		EditAnywhere,
		Category = "LineOfSight"
	)
	UMaterialParameterCollection* SightParams;

	/**
	 * @brief Cache for LaunchTraces() result
	 * @see LaunchTraces()
	 */
	UPROPERTY(
		BlueprintGetter = GetBaseHits,
		Category = "LineOfSight"
	)
	TArray<FHitResult> BaseHits;

	/**
	 * @brief Cache for PreciseTraces() result
	 * @see PreciseTraces()
	 */
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
	/**
	 * @brief Update PlayerLocation and Size param values
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	void UpdateSightParams();

	/**
	 * @brief Draw hits into render texture
	 * @see SightTexture
	 * @param Hits Hits to draw
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	void DrawHits(UPARAM(ref) TArray<FHitResult>& Hits);

	/**
	 * @brief Returns Location of Hit, if it is blocking, Trace End otherwise
	 * @param Hit Hit to use
	 * @return end point of hit
	 */
	UFUNCTION()
	FVector GetEndPoint(const FHitResult& Hit) const;

	/**
	 * @brief Returns the distance point to axis
	 * @param Axis Axis to use
	 * @param Location Point location
	 * @return Distance from point to axis
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	float GetDistanceToAxis(const FVector& Axis, const FVector& Location) const;

	/**
	 * @brief Returns the distance point to X axis
	 * @param Location Point location
	 * @return Distance from point to X axis
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	float GetDistanceToX(const FVector& Location) const;

	/**
	 * @brief Returns the distance point to Y axis
	 * @param Location Point location
	 * @return Distance from point to Y axis
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "LineOfSight"
	)
	float GetDistanceToY(const FVector& Location) const;
};
