// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZoomComponent.generated.h"


class USpringArmComponent;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UZoomComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UZoomComponent();

	virtual void InitializeComponent() override;

	UFUNCTION(
		BlueprintCallable,
		Category = "ZoomComponent"
	)
	void AddDelta(const float Delta);

	UFUNCTION(
		BlueprintCallable,
		Category = "ZoomComponent"
	)
	void Update();

	UFUNCTION(
		BlueprintGetter,
		Category = "ZoomComponent"
	)
	float GetTargetLength() const;

protected:
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ZoomComponent"
	)
	float Speed;

	UPROPERTY(
		BlueprintGetter = "GetTargetLength",
		Category = "ZoomComponent"
	)
	float TargetLength;

	UPROPERTY()
	USpringArmComponent* SpringArmComponent;
};
