// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "RougeType.h"
#include "RougeDamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class GASROUGE_API URougeDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

protected:

	//计算基础伤害
	UFUNCTION(BlueprintNativeEvent)
	float CalculationDamageBase(const FGameplayEffectCustomExecutionParameters& ExecutionParameters,FRougeExcutionHelper& ExcutionHelper) const;

	//计算伤害倍率
	UFUNCTION(BlueprintNativeEvent)
	float CalculationDamagePercent(const FGameplayEffectCustomExecutionParameters& ExecutionParameters,FRougeExcutionHelper& ExcutionHelper) const;

	//计算减伤伤害
	UFUNCTION(BlueprintNativeEvent)
	float CalculationDefencePercent(const FGameplayEffectCustomExecutionParameters& ExecutionParameters,FRougeExcutionHelper& ExcutionHelper) const;

	//计算暴击倍率
	UFUNCTION(BlueprintNativeEvent)
	float CalculationCriticalPercent(const FGameplayEffectCustomExecutionParameters& ExecutionParameters,FRougeExcutionHelper& ExcutionHelper) const;
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
