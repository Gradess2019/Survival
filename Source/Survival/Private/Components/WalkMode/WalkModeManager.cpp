// Copyright Gradess. All Rights Reserved.


#include "Components/WalkMode/WalkModeManager.h"

#include "AbilitySystem/Tags.h"
#include "Characters/SurvivalCharacter.h"
#include "Enums/SurvivalMovementMode.h"


UWalkModeManager::UWalkModeManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

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

void UWalkModeManager::InitializeComponent()
{
	Super::InitializeComponent();

	Character = GetOwner<ASurvivalCharacter>();
	check(Character);

	Character->OnPressMoveKey.AddDynamic(this, &UWalkModeManager::OnPressMoveAction);
}

void UWalkModeManager::ToggleWalkMode()
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

void UWalkModeManager::ToggleCrouch()
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

void UWalkModeManager::ToggleSprint()
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

ESurvivalMovementMode UWalkModeManager::GetDefaultMovementMode() const
{
	return DefaultMovementMode;
}

ESurvivalMovementMode UWalkModeManager::GetCurrentMovementMode() const
{
	return CurrentMovementMode;
}

void UWalkModeManager::SetMovementMode(ESurvivalMovementMode NewMode)
{
	CurrentMovementMode = NewMode;
	UpdateMovementMode();
}

void UWalkModeManager::SetMovementModeToDefaultIfMoving()
{
	if (CurrentMovementMode == ESurvivalMovementMode::Idle) { return; }

	SetMovementMode(DefaultMovementMode);
}

void UWalkModeManager::UpdateMovementMode()
{
	const auto& Tag = MovementTag[CurrentMovementMode];
	Character->ActivateAbility(FGameplayTagContainer(Tag));
}

void UWalkModeManager::OnPressMoveAction(FKey Key)
{
	if (CurrentMovementMode != ESurvivalMovementMode::Idle) { return; }

	SetMovementMode(DefaultMovementMode);
}
