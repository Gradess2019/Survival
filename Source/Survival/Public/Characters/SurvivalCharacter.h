// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GLibGASCharacter.h"
#include "Enums/MovementState.h"
#include "GameFramework/Character.h"
#include "SurvivalCharacter.generated.h"

UCLASS(config=Game)
class ASurvivalCharacter : public AGLibGASCharacter
{
	GENERATED_BODY()

public:
	ASurvivalCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(
		BlueprintGetter = GetMovementState,
		BlueprintSetter = SetMovementState
	)
	EMovementState CurrentMovementState;

	UPROPERTY(
		BlueprintGetter = GetPreviousMovementState,
		BlueprintSetter = SetPreviousMovementState
	)
	EMovementState PreviousMovementState;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	virtual void PostInitializeComponents() override;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnMovementSpeedChanged(const FOnAttributeChangeData& NewValue);

	UFUNCTION(
		BlueprintGetter,
		Category = "SurvivalCharacter"
	)
	EMovementState GetMovementState() const;

	UFUNCTION(
		BlueprintSetter,
		Category = "SurvivalCharacter"
	)
	void SetMovementState(EMovementState NewState);
	
	UFUNCTION(
		BlueprintGetter,
		Category = "SurvivalCharacter"
	)
	EMovementState GetPreviousMovementState() const;

	UFUNCTION(
		BlueprintSetter,
		Category = "SurvivalCharacter"
	)
	void SetPreviousMovementState(EMovementState NewState);


public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
