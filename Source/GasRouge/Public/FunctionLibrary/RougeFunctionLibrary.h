// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RougeFunctionLibrary.generated.h"

class AProjectBase;
class URougeAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GASROUGE_API URougeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static AProjectBase* CreateNewProjectile(TSubclassOf<AProjectBase> ProjectileClass,
		const FTransform& SpawnTransform, AActor* TargetActor, URougeAbilitySystemComponent* AbilityComponent,URougeGameplayAbility* GA);
};
