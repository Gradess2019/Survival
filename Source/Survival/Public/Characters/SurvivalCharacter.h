// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GLibGASCharacter.h"
#include "GameFramework/Character.h"
#include "SurvivalCharacter.generated.h"


#pragma region Forward declarations
class UWalkModeManagerComponent;
class UCameraComponent;
class USpringArmComponent;
class UZoomComponent;
#pragma endregion Forward declarations


#pragma region Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressMoveKey, FKey, Key);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReleaseMoveKey, FKey, Key);
#pragma endregion Delegate declarations


UCLASS(
	Blueprintable,
	BlueprintType,
	ClassGroup = Survival
)
class ASurvivalCharacter : public AGLibGASCharacter
{
	GENERATED_BODY()

public:
	ASurvivalCharacter(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Executes when any MoveAction key was pressed
	 */
	UPROPERTY(
		BlueprintAssignable,
		Category = "SurvivalCharacter"
	)
	FOnPressMoveKey OnPressMoveKey;

	/**
	 * @brief Executes when any MoveAction key was released
	 */
	UPROPERTY(
		BlueprintAssignable,
		Category = "SurvivalCharacter"
	)
	FOnReleaseMoveKey OnReleaseMoveKey;

	virtual void PostInitializeComponents() override;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnMovementSpeedChanged(const FOnAttributeChangeData& Data);
	
	UFUNCTION()
	void OnMoveActionPressed(FKey Key);
	
	UFUNCTION()
	void OnMoveActionReleased(FKey Key);

	UFUNCTION()
	void OnToggleWalkModePressed(FKey Key);

	UFUNCTION()
	void OnToggleCrouchPressed(FKey Key);

	UFUNCTION()
	void OnSprintPressed(FKey Key);

	UFUNCTION()
	void OnSprintReleased(FKey Key);

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Camera"
	)
	USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Camera"
	)
	UCameraComponent* Camera;
	
	/** Follow camera */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Zoom"
	)
	UZoomComponent* Zoom;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "WalkMode"
	)
	UWalkModeManagerComponent* WalkModeManager;
};
