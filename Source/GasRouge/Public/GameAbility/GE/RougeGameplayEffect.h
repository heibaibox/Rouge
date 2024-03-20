// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Pawn/Enemy/EasyEnemyBase.h"
#include "RougeGameplayEffect.generated.h"

class UGameplayEffectAdjustment;
/**
 * 
 */
UCLASS()
class GASROUGE_API URougeGameplayEffect : public UGameplayEffect
{
public:
	GENERATED_UCLASS_BODY()
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category=EffectAdjustment)
	TArray<UGameplayEffectAdjustment*> SourceGrantEffectAdjustments;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category=EffectAdjustment)
	TArray<UGameplayEffectAdjustment*> TargetGrantEffectAdjustments;
};
