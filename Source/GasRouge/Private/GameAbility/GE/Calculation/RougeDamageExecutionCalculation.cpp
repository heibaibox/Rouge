// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GE/Calculation/RougeDamageExecutionCalculation.h"
#include "GameAbility/Attributeset/RougeAttributeSet.h"
#include "Component/RougeAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameAbility/AttributeSet/HealthAttributeSet.h"
#include "GameAbility/AttributeSet/BaseAttributeSet.h"
#include "GameAbility/GA/RougeGameplayAbility.h"

float URougeDamageExecutionCalculation::CalculationDamageBase_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParameters, FRougeExcutionHelper& ExcutionHelper) const
{
	float Attack=ExcutionHelper.SourceAS.Get()->GetAttack();

	float Defence=ExcutionHelper.SourceAS.Get()->GetDefense();

	float DamageBase=FMath::Max(Attack-Defence,0);
	return DamageBase;
}

float URougeDamageExecutionCalculation::CalculationDamagePercent_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParameters, FRougeExcutionHelper& ExcutionHelper) const
{
	return 1.f;
}

float URougeDamageExecutionCalculation::CalculationDefencePercent_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParameters, FRougeExcutionHelper& ExcutionHelper) const
{
	return 1.f;
}

float URougeDamageExecutionCalculation::CalculationCriticalPercent_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParameters, FRougeExcutionHelper& ExcutionHelper) const
{
	float Rate=1.f;
	float CriticalChance=ExcutionHelper.SourceAS.Get()->GetCriticalChance();
	float CriticalRate=ExcutionHelper.SourceAS.Get()->GetCriticalRate();

	float Rand=FMath::FRandRange(0.f,1.f);
	if(Rand<=CriticalChance)
	{
		Rate+=CriticalRate;
		/*ExcutionHelper.Spec->SetSetByCallerMagnitude(FName("Damage. Critical"),1.f);*/
	}
	return Rate;
}

void URougeDamageExecutionCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	FGameplayEffectSpec* Spec=ExecutionParams.GetOwningSpecForPreExecuteMod();
	if(!Spec) return;

	URougeAbilitySystemComponent* SourceASC=Cast<URougeAbilitySystemComponent>(ExecutionParams.GetSourceAbilitySystemComponent());
	URougeAbilitySystemComponent* TargetASC=Cast<URougeAbilitySystemComponent>(ExecutionParams.GetTargetAbilitySystemComponent());

	if(!IsValid(SourceASC)||!IsValid(TargetASC)) return;

	const UBaseAttributeSet* SourceAttributeSet=SourceASC->GetSet<UBaseAttributeSet>();
	const UBaseAttributeSet* TargetAttributeSet=TargetASC->GetSet<UBaseAttributeSet>();
	if(!IsValid(SourceAttributeSet)||!IsValid(TargetAttributeSet)) return;

	const URougeGameplayAbility* SourceAbility=Cast<URougeGameplayAbility>(Spec->GetContext().GetAbilityInstance_NotReplicated());

	FRougeExcutionHelper ExecutionHelper;
	ExecutionHelper.SourceASC=SourceASC;
	ExecutionHelper.TargetASC=TargetASC;
	ExecutionHelper.SourceAS=SourceAttributeSet;
	ExecutionHelper.TargetAS=TargetAttributeSet;
	ExecutionHelper.SourceGA=SourceAbility;
	ExecutionHelper.Spec=Spec;

	FGameplayEffectSpecHandle SpecHandle=FGameplayEffectSpecHandle(Spec);
	
	URougeAbilitySystemComponent::TryApplyGameplayEffectAdjustment(ExecutionHelper.AdjustmentData, SpecHandle, SourceASC, TargetASC);

	//基础伤害
	float DamageBase=CalculationDamageBase(ExecutionParams,ExecutionHelper);

	//伤害倍率
	float DamagePercent=CalculationDamagePercent(ExecutionParams,ExecutionHelper);

	//减伤伤害
	float DefencePercent=CalculationDefencePercent(ExecutionParams,ExecutionHelper);

	//暴击伤害
	float CriticalPercent=CalculationCriticalPercent(ExecutionParams,ExecutionHelper);

	float Damage=DamageBase*DamagePercent*DefencePercent*CriticalPercent;

	Damage*=ExecutionHelper.AdjustmentData.RateValue;
	Damage+=ExecutionHelper.AdjustmentData.ExtraValue;
	if(Damage>0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UHealthAttributeSet::GetFinalDamageAttribute(),EGameplayModOp::Override,Damage));
	}
}
