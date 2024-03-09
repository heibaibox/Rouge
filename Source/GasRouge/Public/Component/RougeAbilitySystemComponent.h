// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RougeType.h"
#include "RougeAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASROUGE_API URougeAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	EPawnCamp Camp=EPawnCamp::Player;
};
