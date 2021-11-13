// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GLibGASCharacter.h"
#include "GameFramework/Character.h"
#include "SurvivalCharacter.generated.h"


#pragma region Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressMoveKey, FKey, Key);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReleaseMoveKey, FKey, Key);
#pragma endregion Delegate declarations


UCLASS(config=Game)
class ASurvivalCharacter : public AGLibGASCharacter
{
	GENERATED_BODY()

public:
	ASurvivalCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(
		BlueprintAssignable,
		Category = "SurvivalCharacter"
	)
	FOnPressMoveKey OnPressMoveKey;
	
	UPROPERTY(
		BlueprintAssignable,
		Category = "SurvivalCharacter"
	)
	FOnReleaseMoveKey OnReleaseMoveKey;
	
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

	void OnMovementSpeedChanged(const FOnAttributeChangeData& Data);

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
