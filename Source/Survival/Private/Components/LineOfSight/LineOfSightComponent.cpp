// Copyright Gradess. All Rights Reserved.


#include "Components/LineOfSight/LineOfSightComponent.h"

#include "Core/GLibMathLibrary.h"
#include "Engine/Canvas.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"


#pragma region Log
DEFINE_LOG_CATEGORY(LogLineOfSight);
#pragma endregion Log


ULineOfSightComponent::ULineOfSightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	TraceNumber = 150;
	PreciseCount = 8;
	PreciseAngle = 0.05f;
	Angle = 140.f;
	ErrorTolerance = 1.f;
	Distance = 6000.f;
	QueryType = UEngineTypes::ConvertToTraceType(ECC_Visibility);

	DebugType = EDrawDebugTrace::None;
	DrawTime = 2.f;
	TraceColor = FLinearColor::Green;
	TraceHitColor = FLinearColor::Red;
}

void ULineOfSightComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	CONDITIONAL_SCOPE_LOG_TIME_FUNC(bMeasureTime);
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FHitResult> Hits;
	LaunchTraces(Hits);
	PreciseHits(BaseHits);

	UpdateSightParams();
	DrawHits(PrecisedHits);
}

FHitResult ULineOfSightComponent::LaunchTrace(
	const FVector& Start,
	const FVector& End,
	const bool bForceDraw
) const
{
	FHitResult Hit;

	UKismetSystemLibrary::LineTraceSingle(
		this,
		Start,
		End,
		QueryType,
		false,
		{},
		bForceDraw ? EDrawDebugTrace::ForOneFrame : DebugType,
		Hit,
		true,
		TraceColor,
		TraceHitColor,
		DrawTime
	);

	return Hit;
}

void ULineOfSightComponent::LaunchTraces(TArray<FHitResult>& OutHits)
{
	BaseHits.Reset(TraceNumber * 2);

	const auto HalfTraceNumber = TraceNumber / 2;
	const auto AnglePerTrace = Angle / TraceNumber;

	const auto Start = GetComponentLocation();
	const auto Forward = GetForwardVector();

	for (int Id = -HalfTraceNumber; Id <= HalfTraceNumber; ++Id)
	{
		const auto TraceAngle = Id * AnglePerTrace;
		const auto TraceDirection = Forward.RotateAngleAxis(TraceAngle, FVector::UpVector);
		const auto End = Start + TraceDirection * Distance;

		BaseHits.Add(LaunchTrace(Start, End));
	}

	OutHits = BaseHits;
}

void ULineOfSightComponent::PreciseHits(TArray<FHitResult>& OutHits)
{
	if (BaseHits.Num() <= 0) { return; }
	PrecisedHits.Reset(BaseHits.Num());

	for (int Id = 0; Id < BaseHits.Num() - 1; ++Id)
	{
		const auto& CurrentBaseHit = BaseHits[Id];
		PrecisedHits.Add(CurrentBaseHit);

		while (Id < BaseHits.Num() - 1)
		{
			Id++;
			const auto& NextBaseHit = BaseHits[Id];

			if (!CurrentBaseHit.bBlockingHit && !NextBaseHit.bBlockingHit)
			{
				PrecisedHits.Add(NextBaseHit);
				continue;
			}

			if (IsAnyHitDistanceEquals(CurrentBaseHit, NextBaseHit))
			{
				continue;
			}
			else
			{
				// We want to continue checking from previous hit in next iteration, that is why we decrement Id
				auto LeftHit = BaseHits[--Id];
				auto RightHit = NextBaseHit;
				
				PreciseHitsByBisectionMethod(LeftHit, RightHit);
				
				PrecisedHits.Add(LeftHit);
				PrecisedHits.Add(RightHit);

				break;
			}
		}
	}

	PrecisedHits.Add(BaseHits.Last());
	
	OutHits = PrecisedHits;
}

void ULineOfSightComponent::PreciseHitsByBisectionMethod(
	FHitResult& LeftHit,
	FHitResult& RightHit
) const
{
	const auto Start = GetComponentLocation();

	for (int32 Count = 0; Count < PreciseCount; ++Count)
	{
		auto LeftDirection = LeftHit.TraceEnd - LeftHit.TraceStart;
		auto RightDirection = RightHit.TraceEnd - RightHit.TraceStart;

		LeftDirection.Normalize();
		RightDirection.Normalize();

		if (IsAngleLessThanPreciseAngle(LeftDirection, RightDirection)) break;

		auto MiddleDirection = LeftDirection + RightDirection;
		MiddleDirection.Normalize();

		auto MiddleEnd = MiddleDirection * Distance + Start;
		auto MiddleHit = LaunchTrace(Start, MiddleEnd);
		MiddleEnd = GetEndPoint(MiddleHit);

		if (IsAnyHitDistanceEquals(LeftHit, MiddleHit))
		{
			LeftHit = MiddleHit;
		}
		else if (IsAnyHitDistanceEquals(RightHit, MiddleHit))
		{
			RightHit = MiddleHit;
		}
	}
}

bool ULineOfSightComponent::IsAngleLessThanPreciseAngle(
	const FVector& LeftDirection,
	const FVector& RightDirection
) const
{
	const auto CurrentAngle =
		UGLibMathLibrary::ShortestAngleBetweenVectorsInDegrees(LeftDirection, RightDirection);
	if (CurrentAngle <= PreciseAngle) { return true; }
	
	return false;
}

bool ULineOfSightComponent::IsAnyDistanceEquals(
	const float FirstDistanceToX,
	const float FirstDistanceToY,
	const float SecondDistanceToX,
	const float SecondDistanceToY
) const
{
	return
		FMath::IsNearlyEqual(FirstDistanceToX, SecondDistanceToX, ErrorTolerance) ||
		FMath::IsNearlyEqual(FirstDistanceToY, SecondDistanceToY, ErrorTolerance);
}

bool ULineOfSightComponent::IsAnyHitDistanceEquals(const FHitResult& FirstHit, const FHitResult& SecondHit) const
{
	const auto DistanceToX = GetDistanceToX(FirstHit.Location);
	const auto DistanceToY = GetDistanceToY(FirstHit.Location);
	
	const auto NextDistanceToX = GetDistanceToX(SecondHit.Location);
	const auto NextDistanceToY = GetDistanceToY(SecondHit.Location);
	
	return IsAnyDistanceEquals(DistanceToX, DistanceToY, NextDistanceToX, NextDistanceToY);
}

const TArray<FHitResult>& ULineOfSightComponent::GetBaseHits() const
{
	return BaseHits;
}

const TArray<FHitResult>& ULineOfSightComponent::GetPrecisedHits() const
{
	return PrecisedHits;
}

void ULineOfSightComponent::UpdateSightParams()
{
	UKismetMaterialLibrary::SetVectorParameterValue(
		this,
		SightParams,
		"PlayerLocation",
		GetOwner()->GetActorLocation()
	);

	UKismetMaterialLibrary::SetScalarParameterValue(
		this,
		SightParams,
		"Size",
		Distance * 2.f
	);
}

void ULineOfSightComponent::DrawHits(TArray<FHitResult>& Hits)
{
	UKismetRenderingLibrary::ClearRenderTarget2D(this, SightTexture);

	UCanvas* Canvas;
	FVector2D Size;
	FDrawToRenderTargetContext Context;
	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, SightTexture, Canvas, Size, Context);

	TArray<FCanvasUVTri> Triangles;

	const auto Center = Size / 2.f;
	const auto VectorToTextureSpaceScale = Center.X / Distance;
	const auto ActorLocation = FVector2D(GetOwner()->GetActorLocation()) * VectorToTextureSpaceScale;
	const auto Color = FColor(255, 255, 255, 0.f);
	for (int32 Id = 0; Id < Hits.Num() - 1; Id++)
	{
		FCanvasUVTri NewTriangle;

		const auto FirstHit = Hits[Id];
		const auto SecondHit = Hits[Id + 1];

		const auto FirstHitLocation = FVector2D(GetEndPoint(FirstHit));
		const auto SecondHitLocation = FVector2D(GetEndPoint(SecondHit));

		NewTriangle.V0_Pos = Center;
		NewTriangle.V1_Pos = FirstHitLocation * VectorToTextureSpaceScale - ActorLocation + Center;
		NewTriangle.V2_Pos = SecondHitLocation * VectorToTextureSpaceScale - ActorLocation + Center;

		NewTriangle.V0_Color = Color;
		NewTriangle.V1_Color = Color;
		NewTriangle.V2_Color = Color;

		Triangles.Add(NewTriangle);
	}
	Canvas->K2_DrawTriangle(nullptr, Triangles);
	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, Context);
}

FVector ULineOfSightComponent::GetEndPoint(const FHitResult& Hit) const
{
	return Hit.bBlockingHit ? Hit.Location : Hit.TraceEnd;
}

float ULineOfSightComponent::GetDistanceToAxis(
	const FVector& Axis,
	const FVector& Location
) const
{
	return FMath::PointDistToLine(Location, Axis, FVector::ZeroVector);
}

float ULineOfSightComponent::GetDistanceToX(const FVector& Location) const
{
	return GetDistanceToAxis(FVector::ForwardVector, Location);
}

float ULineOfSightComponent::GetDistanceToY(const FVector& Location) const
{
	return GetDistanceToAxis(FVector::RightVector, Location);
}