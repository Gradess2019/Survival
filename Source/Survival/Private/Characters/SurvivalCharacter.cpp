// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/SurvivalCharacter.h"
#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WalkMode/WalkModeManagerComponent.h"
#include "Components/Zoom/ZoomComponent.h"

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
	GetCharacterMovement()->JumpZVelocity = 0.f;
	GetCharacterMovement()->AirControl = 0.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->PrimaryComponentTick.bStartWithTickEnabled = false;
	SpringArm->SetRelativeRotation(FRotator(-45.f, -45.f, 0.f));

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Zoom = CreateDefaultSubobject<UZoomComponent>(TEXT("Zoom"));

	WalkModeManager = CreateDefaultSubobject<UWalkModeManagerComponent>(TEXT("WalkModeManager"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASurvivalCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASurvivalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASurvivalCharacter::MoveRight);

	PlayerInputComponent->BindAction("MoveAction", IE_Pressed, this, &ASurvivalCharacter::OnMoveActionPressed);
	PlayerInputComponent->BindAction("MoveAction", IE_Released, this, &ASurvivalCharacter::OnMoveActionReleased);

	PlayerInputComponent->BindAction("ToggleWalkMode", IE_Pressed, this, &ASurvivalCharacter::OnToggleWalkModePressed);
	PlayerInputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &ASurvivalCharacter::OnToggleCrouchPressed);
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASurvivalCharacter::OnSprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASurvivalCharacter::OnSprintReleased);
}

void ASurvivalCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
	GetCharacterMovement()->MaxWalkSpeedCrouched = Data.NewValue;
}

void ASurvivalCharacter::OnMoveActionPressed(FKey Key)
{
	OnPressMoveKey.Broadcast(Key);
}

void ASurvivalCharacter::OnMoveActionReleased(FKey Key)
{
	OnReleaseMoveKey.Broadcast(Key);
}

void ASurvivalCharacter::OnToggleWalkModePressed(FKey Key)
{
	WalkModeManager->ToggleWalkMode();
}

void ASurvivalCharacter::OnToggleCrouchPressed(FKey Key)
{
	WalkModeManager->ToggleCrouch();
}

void ASurvivalCharacter::OnSprintPressed(FKey Key)
{
	WalkModeManager->ToggleSprint();
}

void ASurvivalCharacter::OnSprintReleased(FKey Key)
{
	WalkModeManager->ToggleSprint();
}

void ASurvivalCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const auto PlayerSet = GenericGetAttributes<UPlayerAttributeSet>();
	
	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(PlayerSet->GetMovementSpeedAttribute())
		.AddUObject(this, &ASurvivalCharacter::OnMovementSpeedChanged);

	OnPressMoveKey.AddDynamic(WalkModeManager, &UWalkModeManagerComponent::OnPressMoveAction);
}

void ASurvivalCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = SpringArm->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASurvivalCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = SpringArm->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
