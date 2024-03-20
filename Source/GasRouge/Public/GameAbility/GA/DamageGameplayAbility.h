// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameAbility/GA/RougeGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"

class AEnemyBase;
/**
 * 
 */
UCLASS()
class GASROUGE_API UDamageGameplayAbility : public URougeGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor,float Value=1.f);
	
};
