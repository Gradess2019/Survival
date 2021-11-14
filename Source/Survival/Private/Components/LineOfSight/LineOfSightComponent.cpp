// Copyright Gradess. All Rights Reserved.


#include "Components/LineOfSight/LineOfSightComponent.h"

#include "Core/GLibMathLibrary.h"
#include "Engine/Canvas.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "VisualLogger/VisualLogger.h"


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
	Angle = 100.f;
	Distance = 2000.f;
	QueryType = UEngineTypes::ConvertToTraceType(ECC_Visibility);

	DebugType = EDrawDebugTrace::None;
	DrawTime = 2.f;
	TraceColor = FLinearColor::Green;
	TraceHitColor = FLinearColor::Red;
}

void ULineOfSightComponent::BeginPlay()
{
	Super::BeginPlay();
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

	UpdateSightParams();
	DrawHits(Hits);
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

void ULineOfSightComponent::LaunchTraces(TArray<FHitResult>& Hits) const
{
	Hits.Reset(TraceNumber * 2);

	const auto HalfAngle = Angle / 2.f; // 45
	const auto HalfTraceNumber = TraceNumber / 2; // 2
	const auto AnglePerTrace = Angle / TraceNumber; // 22

	const auto Start = GetComponentLocation();
	const auto Forward = GetForwardVector();

	TArray<FHitResult> BaseHits;
	BaseHits.Reserve(Hits.Num());
	for (int Id = -HalfTraceNumber; Id <= HalfTraceNumber; ++Id)
	{
		const auto TraceAngle = Id * AnglePerTrace;
		const auto TraceDirection = Forward.RotateAngleAxis(TraceAngle, FVector::UpVector);
		const auto End = Start + TraceDirection * Distance;

		BaseHits.Add(LaunchTrace(Start, End));
	}

	for (int Id = 0; Id < BaseHits.Num() - 1; ++Id)
	{
		const auto& CurrentBaseHit = BaseHits[Id];
		Hits.Add(CurrentBaseHit);

		const auto DistanceToX = [&]()
		{
			return FMath::PointDistToLine(CurrentBaseHit.Location, FVector::ForwardVector, FVector::ZeroVector);
		}();

		const auto DistanceToY = [&]()
		{
			return FMath::PointDistToLine(CurrentBaseHit.Location, FVector::RightVector, FVector::ZeroVector);
		}();

		for (; Id < BaseHits.Num() - 1;)
		{
			Id++;
			const auto& NextBaseHit = BaseHits[Id];

			if (!CurrentBaseHit.bBlockingHit && !NextBaseHit.bBlockingHit)
			{
				Hits.Add(NextBaseHit);
				continue;
			}

			const auto NextDistanceToX = [&]()
			{
				return FMath::PointDistToLine(NextBaseHit.Location, FVector::ForwardVector, FVector::ZeroVector);
			}();

			const auto NextDistanceToY = [&]()
			{
				return FMath::PointDistToLine(NextBaseHit.Location, FVector::RightVector, FVector::ZeroVector);
			}();

			if (FMath::IsNearlyEqual(DistanceToX, NextDistanceToX, 1.f) || FMath::IsNearlyEqual(
				DistanceToY, NextDistanceToY, 1.f))
			{
				continue;
			}
			else
			{
				auto LeftHit = BaseHits[Id - 1];
				auto RightHit = NextBaseHit;

				for (int32 Count = 0; Count < PreciseCount; ++Count)
				{
					auto LeftDirection = LeftHit.TraceEnd - LeftHit.TraceStart;
					auto RightDirection = RightHit.TraceEnd - RightHit.TraceStart;

					LeftDirection.Normalize();
					RightDirection.Normalize();

					const auto CurrentAngle = UGLibMathLibrary::ShortestAngleBetweenVectorsInDegrees(
						LeftDirection, RightDirection);
					if (CurrentAngle <= PreciseAngle) { break; }

					auto MiddleDirection = LeftDirection + RightDirection;
					MiddleDirection.Normalize();

					auto MiddleEnd = MiddleDirection * Distance + Start;
					auto MiddleHit = LaunchTrace(Start, MiddleEnd);
					MiddleEnd = GetEndPoint(MiddleHit);

					const auto MiddleDistanceToX = [&]()
					{
						return FMath::PointDistToLine(MiddleHit.Location, FVector::ForwardVector, FVector::ZeroVector);
					}();

					const auto MiddleDistanceToY = [&]()
					{
						return FMath::PointDistToLine(MiddleHit.Location, FVector::RightVector, FVector::ZeroVector);
					}();

					if (FMath::IsNearlyEqual(DistanceToX, MiddleDistanceToX, 1.f) || FMath::IsNearlyEqual(
						DistanceToY, MiddleDistanceToY, 1.f))
					{
						LeftHit = MiddleHit;
					}
					else if (FMath::IsNearlyEqual(NextDistanceToX, MiddleDistanceToX, 1.f) || FMath::IsNearlyEqual(
						NextDistanceToY, MiddleDistanceToY, 1.f))
					{
						RightHit = MiddleHit;
					}
				}
				Hits.Add(LeftHit);
				Hits.Add(RightHit);

				Id--;
				break;
			}
		}
	}

	Hits.Add(BaseHits.Last());

	// for (const auto& Hit : Hits)
	// {
	// 	LaunchTrace(Hit.TraceStart, Hit.TraceEnd, true);
	// }
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
	const auto TextureBorderMargin = 0.f;
	const auto VectorToTextureSpaceScale = Center.X / (Distance + TextureBorderMargin);
	const auto ActorLocation = FVector2D(GetOwner()->GetActorLocation()) * VectorToTextureSpaceScale;
	const auto Color = FColor(255, 255, 255, 0.f);
	for (int32 Id = 0; Id < Hits.Num() - 1; Id++)
	{
		FCanvasUVTri NewTriangle;

		const auto FirstHit = Hits[Id];
		const auto SecondHit = Hits[Id + 1];

		const auto FirstHitLocation =
			FirstHit.bBlockingHit ? FVector2D(FirstHit.Location) : FVector2D(FirstHit.TraceEnd);
		const auto SecondHitLocation =
			SecondHit.bBlockingHit ? FVector2D(SecondHit.Location) : FVector2D(SecondHit.TraceEnd);

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
