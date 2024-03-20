// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GA/DamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Pawn/Enemy/EnemyBase.h"
#include "GameAbility/AttributeSet/HealthAttributeSet.h"
#include "GameAbility/GE/RougeGameplayEffect.h"
#include "GameAbility/GE/Calculation/RougeDamageExecutionCalculation.h"


void UDamageGameplayAbility::CauseDamage(AActor* TargetActor, float Value)
{
	if (TargetActor == nullptr || GetAbilitySystemComponentFromActorInfo() == nullptr)
	{
		return;
	}

	URougeGameplayEffect* DamageEffective=NewObject<URougeGameplayEffect>(URougeGameplayEffect::StaticClass());
	if(DamageEffective)
	{
		DamageEffective->DurationPolicy=EGameplayEffectDurationType::Instant;
		DamageEffective->Modifiers.SetNum(1);
		FGameplayModifierInfo& ModifierInfo = DamageEffective->Modifiers[0];
		ModifierInfo.Attribute=UHealthAttributeSet::GetFinalDamageAttribute();
		ModifierInfo.ModifierOp = EGameplayModOp::Additive;
		ModifierInfo.ModifierMagnitude=FScalableFloat(Value);
		DamageEffective->Executions.SetNum(1);
		FGameplayEffectExecutionDefinition& ExecutionInfo = DamageEffective->Executions[0];
		ExecutionInfo.CalculationClass=URougeDamageExecutionCalculation::StaticClass();

		FGameplayEffectContext* Data=new FGameplayEffectContext;
		Data->AddInstigator(GetActorInfo().OwnerActor.Get(),GetActorInfo().AvatarActor.Get());
		Data->SetAbility(this);
		
		FGameplayEffectContextHandle DataHandle=FGameplayEffectContextHandle(Data);
		FGameplayEffectSpec GESpec = FGameplayEffectSpec(DamageEffective, DataHandle, 1.f);

		
		if(UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(GESpec,TargetASC);
	}
}
