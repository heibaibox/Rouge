// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GE/RougeGameplayEffect.h"

URougeGameplayEffect::URougeGameplayEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	PRAGMA_DISABLE_DEPRECATION_WARNINGS
	DurationPolicy = EGameplayEffectDurationType::Instant;
	bExecutePeriodicEffectOnApplication = true;
	PeriodicInhibitionPolicy = EGameplayEffectPeriodInhibitionRemovedPolicy::NeverReset;

	StackingType = EGameplayEffectStackingType::None;
	StackLimitCount = 0;
	StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;
	StackPeriodResetPolicy = EGameplayEffectStackingPeriodPolicy::ResetOnSuccessfulApplication;
	bRequireModifierSuccessToTriggerCues = true;
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
}
