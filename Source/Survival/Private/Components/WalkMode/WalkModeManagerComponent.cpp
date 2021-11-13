// Copyright Gradess. All Rights Reserved.


#include "Components/WalkMode/WalkModeManagerComponent.h"

#include "AbilitySystem/Tags.h"
#include "Characters/SurvivalCharacter.h"
#include "Enums/SurvivalMovementMode.h"


UWalkModeManagerComponent::UWalkModeManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bWantsInitializeComponent = true;
	
	DefaultMovementMode = ESurvivalMovementMode::Walk;
	PreviousMovementMode = ESurvivalMovementMode::Idle;
	CurrentMovementMode = ESurvivalMovementMode::Idle;

	MovementTag = {
		{ESurvivalMovementMode::Idle, FGameplayTag::RequestGameplayTag(MovementIdleTagName)},
		{ESurvivalMovementMode::Crouch, FGameplayTag::RequestGameplayTag(MovementCrouchTagName)},
		{ESurvivalMovementMode::Walk, FGameplayTag::RequestGameplayTag(MovementWalkTagName)},
		{ESurvivalMovementMode::Run, FGameplayTag::RequestGameplayTag(MovementRunTagName)},
		{ESurvivalMovementMode::Sprint, FGameplayTag::RequestGameplayTag(MovementSprintTagName)},
	};
}

void UWalkModeManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Character = GetOwner<ASurvivalCharacter>();
	check(Character);
}

void UWalkModeManagerComponent::ToggleWalkMode()
{
	switch (DefaultMovementMode)
	{
	case ESurvivalMovementMode::Walk:
		{
			DefaultMovementMode = ESurvivalMovementMode::Run;
			break;
		}
	case ESurvivalMovementMode::Run:
		{
			DefaultMovementMode = ESurvivalMovementMode::Walk;
			break;
		}
	default: return;
	}

	SetMovementModeToDefaultIfMoving();
}

void UWalkModeManagerComponent::ToggleCrouch()
{
	switch (DefaultMovementMode)
	{
	case ESurvivalMovementMode::Sprint: return;
	case ESurvivalMovementMode::Crouch:
		{
			DefaultMovementMode = PreviousMovementMode;
			PreviousMovementMode = ESurvivalMovementMode::Crouch;
			break;
		}
	case ESurvivalMovementMode::Idle:
	case ESurvivalMovementMode::Walk:
	case ESurvivalMovementMode::Run:
		{
			PreviousMovementMode = DefaultMovementMode;
			DefaultMovementMode = ESurvivalMovementMode::Crouch;
			break;
		}
	default: return;
	}

	SetMovementModeToDefaultIfMoving();
}

void UWalkModeManagerComponent::ToggleSprint()
{
	switch (DefaultMovementMode)
	{
	case ESurvivalMovementMode::Sprint:
		{
			DefaultMovementMode = PreviousMovementMode;
			PreviousMovementMode = ESurvivalMovementMode::Run;
			break;
		}
	case ESurvivalMovementMode::Idle:
	case ESurvivalMovementMode::Crouch:
	case ESurvivalMovementMode::Walk:
	case ESurvivalMovementMode::Run:
		{
			PreviousMovementMode = DefaultMovementMode;
			DefaultMovementMode = ESurvivalMovementMode::Sprint;
			break;
		}
	default: return;
	}

	SetMovementModeToDefaultIfMoving();
}

ESurvivalMovementMode UWalkModeManagerComponent::GetDefaultMovementMode() const
{
	return DefaultMovementMode;
}

ESurvivalMovementMode UWalkModeManagerComponent::GetCurrentMovementMode() const
{
	return CurrentMovementMode;
}

UWalkModeManagerComponent* UWalkModeManagerComponent::GetWalkModeManager(const AActor* Actor)
{
	if (!IsValid(Actor)) { return nullptr; }
	return Actor->FindComponentByClass<UWalkModeManagerComponent>();
}

void UWalkModeManagerComponent::SetCurrentMovementMode(ESurvivalMovementMode NewMode)
{
	CurrentMovementMode = NewMode;
	UpdateMovementMode();
}

void UWalkModeManagerComponent::SetMovementModeToDefaultIfMoving()
{
	if (CurrentMovementMode == ESurvivalMovementMode::Idle) { return; }

	SetCurrentMovementMode(DefaultMovementMode);
}

void UWalkModeManagerComponent::UpdateMovementMode()
{
	const auto& Tag = MovementTag[CurrentMovementMode];
	Character->ActivateAbility(FGameplayTagContainer(Tag));
}

void UWalkModeManagerComponent::OnPressMoveAction(FKey Key)
{
	if (CurrentMovementMode != ESurvivalMovementMode::Idle) { return; }

	SetCurrentMovementMode(DefaultMovementMode);
}
