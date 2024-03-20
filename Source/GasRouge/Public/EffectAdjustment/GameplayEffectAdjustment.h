// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RougeType.h"
#include "GameplayEffectAdjustment.generated.h"

/**
 * 
 */
UCLASS()
class GASROUGE_API UGameplayEffectAdjustment : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	bool CanApplyEffectAdjustment(const FGameplayEffectSpecHandle& EffectSpecHandle, UAbilitySystemComponent* SourceASC,
	   UAbilitySystemComponent* TargetASC);

	UFUNCTION(BlueprintNativeEvent)
	void TryApplyEffectAdjustment(FGameplayEffectAdjustmentData& AdjustmentData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Adjustment)
	FGameplayEffectAdjustmentData Adjustment;
};
