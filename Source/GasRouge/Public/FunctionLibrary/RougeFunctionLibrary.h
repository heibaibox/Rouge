// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RougeFunctionLibrary.generated.h"

class AProjectBase;
class URougeAbilitySystemComponent;
class ACombatGameMode;
class APickUpActor;
/**
 * 
 */
UCLASS()
class GASROUGE_API URougeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static AProjectBase* CreateNewProjectile(AGameModeBase* GameModeBase,TSubclassOf<AProjectBase> ProjectileClass,
		const FTransform& SpawnTransform, AActor* TargetActor, URougeAbilitySystemComponent* AbilityComponent,URougeGameplayAbility* GA);

	UFUNCTION(BlueprintCallable)
	static APickUpActor* CreateNewPickUpActor(AGameModeBase* GameModeBase,TSubclassOf<APickUpActor> PickUpActorClass,const FTransform& SpawnTransform);
	
	UFUNCTION(BlueprintCallable)
	static bool GetClosestEnemies(const AActor* InActor, TArray<AEnemyBase*>& OutEnemies, int32 MaxNum = 1);

	UFUNCTION(BlueprintCallable)
	static ACombatGameMode* GetCombatGameMode(const UObject* WorldContext);
	
};
