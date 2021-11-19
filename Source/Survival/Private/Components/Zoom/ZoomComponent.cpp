// Copyright Gradess. All Rights Reserved.


#include "Components/Zoom/ZoomComponent.h"

#include "GameFramework/SpringArmComponent.h"


UZoomComponent::UZoomComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bWantsInitializeComponent = true;
}

void UZoomComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SpringArmComponent = GetOwner()->FindComponentByClass<USpringArmComponent>();
	check(SpringArmComponent);

	TargetLength = SpringArmComponent->TargetArmLength;
}

void UZoomComponent::AddDelta(const float Delta)
{
	TargetLength += Delta * Power * Invert ? -1.f: 1.f;
}

void UZoomComponent::Update()
{
	const auto DeltaTime = GetWorld()->DeltaTimeSeconds;

	SpringArmComponent->TargetArmLength = FMath::Lerp(SpringArmComponent->TargetArmLength, TargetLength, DeltaTime * Speed);
}

float UZoomComponent::GetTargetLength() const
{
	return TargetLength;
}

