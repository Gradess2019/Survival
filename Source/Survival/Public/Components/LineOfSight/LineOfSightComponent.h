// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LineOfSightComponent.generated.h"


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
	void LaunchTraces(TArray<FHitResult>& Hits) const;

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
	float Angle;

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

#pragma region Debug
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
};
