// Copyright Gradess. All Rights Reserved.


#include "Components/Zoom/ZoomComponent.h"

#include "GameFramework/SpringArmComponent.h"


UZoomComponent::UZoomComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bWantsInitializeComponent = true;

	Speed = 5.f;
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
	TargetLength += Delta;
}

void UZoomComponent::Update()
{
	const auto DeltaTime = GetWorld()->DeltaTimeSeconds;

	SpringArmComponent->TargetArmLength = FMath::Lerp(SpringArmComponent->TargetArmLength, TargetLength, DeltaTime);
}

float UZoomComponent::GetTargetLength() const
{
	return TargetLength;
}

