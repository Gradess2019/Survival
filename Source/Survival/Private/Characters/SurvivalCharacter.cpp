// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/SurvivalCharacter.h"
#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ASurvivalCharacter

ASurvivalCharacter::ASurvivalCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass(TEXT("AttributeSet"), UPlayerAttributeSet::StaticClass()))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASurvivalCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASurvivalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASurvivalCharacter::MoveRight);
}

void ASurvivalCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& NewValue)
{
	GetCharacterMovement()->MaxWalkSpeed = NewValue.NewValue;
}

void ASurvivalCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const auto PlayerSet = GenericGetAttributes<UPlayerAttributeSet>();
	
	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(PlayerSet->GetMovementSpeedAttribute())
		.AddUObject(this, &ASurvivalCharacter::OnMovementSpeedChanged);
}

void ASurvivalCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = CameraBoom->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASurvivalCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = CameraBoom->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}