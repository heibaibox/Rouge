// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RougeGameplayAbility.generated.h"

class APawnBase;
/**
 * 
 */
UCLASS()
class GASROUGE_API URougeGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	APawnBase* GetOwnerPawn();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	APawnBase* GetAvatarPawn();

};
