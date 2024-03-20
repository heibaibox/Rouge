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
private:
	FDelegateHandle EffectAppliedToSelfHandle;

	FDelegateHandle EffectRemovedFromSelfHandle;
protected:
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, FActiveEffectAdjustmentHandle> SourceActiveEffectAdjustmentContainer;
    	
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, FActiveEffectAdjustmentHandle> TargetActiveEffectAdjustmentContainer;
public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	EPawnCamp Camp=EPawnCamp::Player;
	
protected:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void HandleGameplayEffectAppliedToSelf(UAbilitySystemComponent* Source, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);

	UFUNCTION()
	void HandleGameplayEffectRemovedFromSelf(const FActiveGameplayEffect& ActiveEffect);

public:
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	static void TryApplyGameplayEffectAdjustment(FGameplayEffectAdjustmentData& AdjustmentData,const FGameplayEffectSpecHandle& EffectSpecHandle,
		URougeAbilitySystemComponent* SourceASC,URougeAbilitySystemComponent* TargetASC);
};
