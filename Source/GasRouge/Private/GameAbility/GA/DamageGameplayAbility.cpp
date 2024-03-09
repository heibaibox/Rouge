// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GA/DamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "RougeGameplayTags.h"
#include "GameAbility/AttributeSet/BaseAttributeSet.h"
#include "GameAbility/AttributeSet/HealthAttributeSet.h"

void UDamageGameplayAbility::CauseDamage(AActor* TargetActor, float Value)
{
	if (DamageEffectClass == nullptr || TargetActor == nullptr || GetAbilitySystemComponentFromActorInfo() == nullptr)
	{
		return;
	}
	/*if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		const FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
		FGameplayEffectSpec* Spec = DamageSpecHandle.Data.Get();
		if (Spec)
		{
			FGameplayEffectContextHandle ContextHandle = Spec->GetContext();
			FGameplayEffectContext* Context = ContextHandle.Get();
		
		}
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, UHealthAttributeSet::GetFinalDamageAttribute(), Value);
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), TargetASC);
	}*/
}
