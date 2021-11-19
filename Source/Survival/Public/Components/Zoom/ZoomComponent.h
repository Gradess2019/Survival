// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZoomComponent.generated.h"


#pragma region Forward declarations
class USpringArmComponent;
#pragma endregion Forward declarations


/**
 * @brief The component that allows zoom in/out by delta or exact value using spring arm component
 */
UCLASS(
	Blueprintable,
	BlueprintType,
	ClassGroup = Survival,
	meta = (
		BlueprintSpawnableComponent
	)
)
class SURVIVAL_API UZoomComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UZoomComponent();

	virtual void InitializeComponent() override;

	/**
	 * @brief Adds some value to TargetLength
	 * @see TargetLength
	 * @param Delta Value to add
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "ZoomComponent"
	)
	void AddDelta(const float Delta);

	/**
	 * @brief Interpolates length from current length to TargetLength
	 * @see TargetLength
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "ZoomComponent"
	)
	void Update();

	/**
	 * @brief Sets new value to TargetLength and clamps that
	 * @see TargetLength
	 * @param NewLength New length to use
	 */
	UFUNCTION(
		BlueprintSetter,
		Category = "ZoomComponent"
	)
	void SetTargetLength(const float NewLength);

	/**
	 * @brief Returns current TargetLength value
	 * @see TargetLength
	 * @return TargetLength
	 */
	UFUNCTION(
		BlueprintGetter,
		Category = "ZoomComponent"
	)
	float GetTargetLength() const;

	/**
	 * @brief Returns spring arm component that is being used by current zoom component
	 * @see SpringArmComponent
	 * @return SpringArmComponent
	 */
	UFUNCTION(
		BlueprintGetter,
		Category = "ZoomComponent"
	)
	USpringArmComponent* GetSpringArmComponent() const;

protected:
	/**
	 * @brief Speed of interpolation
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ZoomComponent"
	)
	float Speed = 5.f;

	/**
	 * @brief Multiplier for delta value
	 * It allows to zoom in/out faster/slower
	 * @see AddDelta()
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ZoomComponent"
	)
	float Power = 60.f;

	/**
	 * @brief Min length for TargetLength
	 * @see TargetLength
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ZoomComponent"
	)
	float MinLength = 500.f;

	/**
	 * @brief Max length for TargetLength
	 * @see TargetLength
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ZoomComponent"
	)
	float MaxLength = 2000.f;

	/**
	 * @brief Should we invert delta value or not
	 * @see AddDelta()
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ZoomComponent"
	)
	bool Invert = true;

	/**
	 * @brief Target length for spring arm
	 */
	UPROPERTY(
		BlueprintGetter = "GetTargetLength",
		BlueprintSetter = "SetTargetLength",
		Category = "ZoomComponent"
	)
	float TargetLength;

private:
	/**
	 * @brief Spring arm component to zoom in/out
	 */
	UPROPERTY(
		BlueprintGetter = "GetSpringArmComponent",
		Category = "ZoomComponent"
	)
	USpringArmComponent* SpringArmComponent;
};
