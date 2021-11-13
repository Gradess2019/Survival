// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "WalkModeManagerComponent.generated.h"


#pragma region Forward declarations
class ASurvivalCharacter;
enum class ESurvivalMovementMode : uint8;
#pragma endregion Forward declarations


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UWalkModeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWalkModeManagerComponent();
	virtual void InitializeComponent() override;

	UFUNCTION(
		BlueprintCallable,
		Category = "WalMode"
	)
	void ToggleWalkMode();

	UFUNCTION(
		BlueprintCallable,
		Category = "WalMode"
	)
	void ToggleCrouch();

	UFUNCTION(
		BlueprintCallable,
		Category = "WalMode"
	)
	void ToggleSprint();

	UFUNCTION(
		BlueprintSetter,
		Category = "WalkMode"
	)
	void SetCurrentMovementMode(ESurvivalMovementMode NewMode);

	UFUNCTION(
		BlueprintGetter,
		Category = "WalMode"
	)
	ESurvivalMovementMode GetDefaultMovementMode() const;

	UFUNCTION(
		BlueprintGetter,
		Category = "WalMode"
	)
	ESurvivalMovementMode GetCurrentMovementMode() const;

	UFUNCTION(
		BlueprintPure,
		Category = "WalkMode"
	)
	static UWalkModeManagerComponent* GetWalkModeManager(const AActor* Actor);

protected:
	UFUNCTION()
	void SetMovementModeToDefaultIfMoving();

	UFUNCTION()
	void UpdateMovementMode();

	UFUNCTION()
	void OnPressMoveAction(FKey Key);

private:
	UPROPERTY(
		BlueprintGetter = "GetDefaultMovementMode",
		Category = "WalMode"
	)
	ESurvivalMovementMode DefaultMovementMode;

	UPROPERTY()
	ESurvivalMovementMode PreviousMovementMode;

	UPROPERTY(
		BlueprintSetter = "SetCurrentMovementMode",
		BlueprintGetter = "GetCurrentMovementMode",
		Category = "WalMode"
	)
	ESurvivalMovementMode CurrentMovementMode;

	UPROPERTY()
	ASurvivalCharacter* Character;

	UPROPERTY(
		EditAnywhere,
		Category = "WalkMode"
	)
	TMap<ESurvivalMovementMode, FGameplayTag> MovementTag;
};
