// Copyright Gradess. All Rights Reserved.


#include "Components/LineOfSight/LineOfSightComponent.h"

#include "Engine/Canvas.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"


ULineOfSightComponent::ULineOfSightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	TraceNumber = 30;
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
	SCOPE_LOG_TIME_FUNC();
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FHitResult> Hits;
	LaunchTraces(Hits);

	UpdateSightParams();
	DrawHits(Hits);
}

FHitResult ULineOfSightComponent::LaunchTrace(
	const FVector& Start,
	const FVector& End
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
		DebugType,
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
	
	for (int Id = -HalfTraceNumber; Id <= HalfTraceNumber; ++Id)
	{
		const auto TraceAngle = Id * AnglePerTrace;
		const auto TraceDirection = Forward.RotateAngleAxis(TraceAngle, FVector::UpVector);
		const auto End = Start + TraceDirection * Distance;

		Hits.Add(LaunchTrace(Start, End));
	}
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
	const auto TextureBorderMargin = Distance * 0.1;
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
