// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectAdjustment/GameplayEffectAdjustment.h"

void UGameplayEffectAdjustment::TryApplyEffectAdjustment_Implementation(FGameplayEffectAdjustmentData& AdjustmentData)
{
	AdjustmentData=Adjustment;
}
