// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/AttributeSet/HealthAttributeSet.h"

#include "GameplayEffectExtension.h"

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute==GetFinalDamageAttribute())
	{
		float DamageAmount=GetFinalDamage();
		float OldHealth=GetHealth();
		float OldShield=GetShield();
		if(OldShield>=DamageAmount)
		{
			SetShield(FMath::Clamp(GetShield()-DamageAmount,0.f,GetMaxShield()));
		}
		else
		{
			DamageAmount-=OldShield;
			SetShield(0.f);
			SetHealth(FMath::Clamp(GetHealth()-DamageAmount,0.f,GetMaxHealth()));
		}
        
		SetFinalDamage(0.f);
	}
	
}
