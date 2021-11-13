// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/GLibBaseAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

UCLASS(
	Blueprintable,
	BlueprintType,
	ClassGroup = Survival
)
class SURVIVAL_API UPlayerAttributeSet : public UGLibBaseAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_MovementSpeed,
		Category = "Attributes"
	)
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MovementSpeed);

	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_MaxMovementSpeed,
		Category = "Attributes"
	)
	FGameplayAttributeData MaxMovementSpeed;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxMovementSpeed);

	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_Endurance,
		Category = "Attributes"
	)
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Endurance);

	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_MaxEndurance,
		Category = "Attributes"
	)
	FGameplayAttributeData MaxEndurance;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxEndurance);

	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_Thirst,
		Category = "Attributes"
	)
	FGameplayAttributeData Thirst;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Thirst);

	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_MaxThirst,
		Category = "Attributes"
	)
	FGameplayAttributeData MaxThirst;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxThirst);

	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_Hunger,
		Category = "Attributes"
	)
	FGameplayAttributeData Hunger;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Hunger);

	UPROPERTY(
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_MaxHunger,
		Category = "Attributes"
	)
	FGameplayAttributeData MaxHunger;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxHunger);


	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Endurance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxEndurance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Thirst(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxThirst(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Hunger(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHunger(const FGameplayAttributeData& OldValue);
};
