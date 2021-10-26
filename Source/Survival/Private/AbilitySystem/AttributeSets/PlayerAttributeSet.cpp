// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetEnduranceAttribute())
	{
		SetMovementSpeed(FMath::Clamp(GetMovementSpeed(), 0.f, GetMaxMovementSpeed()));
	}
	else if (Data.EvaluatedData.Attribute == GetEnduranceAttribute())
	{
		SetEndurance(FMath::Clamp(GetEndurance(), 0.f, GetMaxEndurance()));
	}
	else if (Data.EvaluatedData.Attribute == GetThirstAttribute())
	{
		SetThirst(FMath::Clamp(GetThirst(), 0.f, GetMaxThirst()));
	}
	else if (Data.EvaluatedData.Attribute == GetHungerAttribute())
	{
		SetHunger(FMath::Clamp(GetHunger(), 0.f, GetMaxHunger()));
	}
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxEndurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Thirst, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxThirst, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Hunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxHunger, COND_None, REPNOTIFY_Always);
}

void UPlayerAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MovementSpeed, OldValue);
}

void UPlayerAttributeSet::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxMovementSpeed, OldValue);
}

void UPlayerAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Endurance, OldValue);
}

void UPlayerAttributeSet::OnRep_MaxEndurance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxEndurance, OldValue);
}

void UPlayerAttributeSet::OnRep_Thirst(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Thirst, OldValue);
}

void UPlayerAttributeSet::OnRep_MaxThirst(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxThirst, OldValue);
}

void UPlayerAttributeSet::OnRep_Hunger(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Hunger, OldValue);
}

void UPlayerAttributeSet::OnRep_MaxHunger(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxHunger, OldValue);
}
