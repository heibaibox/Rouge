// Fill out your copyright notice in the Description page of Project Settings.


#include "GasRouge/Public/Component/RougeAbilitySystemComponent.h"
#include "EffectAdjustment/GameplayEffectAdjustment.h"
#include "GameAbility/GE/RougeGameplayEffect.h"

void URougeAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	if(!EffectAppliedToSelfHandle.IsValid())
	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this,&URougeAbilitySystemComponent::HandleGameplayEffectAppliedToSelf);

	if(!EffectRemovedFromSelfHandle.IsValid())
	OnAnyGameplayEffectRemovedDelegate().AddUObject(this,&URougeAbilitySystemComponent::HandleGameplayEffectRemovedFromSelf);
}

void URougeAbilitySystemComponent::TryApplyGameplayEffectAdjustment(FGameplayEffectAdjustmentData& AdjustmentData,
	const FGameplayEffectSpecHandle& EffectSpecHandle, URougeAbilitySystemComponent* SourceASC,
	URougeAbilitySystemComponent* TargetASC)
{
	for(auto& Pair:SourceASC->SourceActiveEffectAdjustmentContainer)
	{
		FActiveEffectAdjustmentHandle AdjustmentHandle = Pair.Value;
		if(AdjustmentHandle.EffectAdjustment)
		{
			if(AdjustmentHandle.EffectAdjustment->CanApplyEffectAdjustment(EffectSpecHandle, SourceASC, TargetASC))
			{
				AdjustmentHandle.EffectAdjustment->TryApplyEffectAdjustment(AdjustmentData);
			}
		}
	}

	for(auto& Pair:TargetASC->TargetActiveEffectAdjustmentContainer)
	{
		FActiveEffectAdjustmentHandle AdjustmentHandle=Pair.Value;
		if(AdjustmentHandle.EffectAdjustment)
		{
			if(AdjustmentHandle.EffectAdjustment->CanApplyEffectAdjustment(EffectSpecHandle,SourceASC,TargetASC))
			{
				AdjustmentHandle.EffectAdjustment->TryApplyEffectAdjustment(AdjustmentData);
			}
		}
	}
}

void URougeAbilitySystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnActiveGameplayEffectAddedDelegateToSelf.Remove(EffectAppliedToSelfHandle);

	OnAnyGameplayEffectRemovedDelegate().Remove(EffectRemovedFromSelfHandle);
}

void URougeAbilitySystemComponent::HandleGameplayEffectAppliedToSelf(UAbilitySystemComponent* Source,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	if(!IsValid(SpecApplied.Def)) return;

	URougeGameplayEffect* GECDO=Cast<URougeGameplayEffect>(SpecApplied.Def);
	if(!IsValid(GECDO)) return;

	if(!GECDO->SourceGrantEffectAdjustments.IsEmpty())
	{
		for(UGameplayEffectAdjustment* Adjustment:GECDO->SourceGrantEffectAdjustments)
		{
			FActiveEffectAdjustmentHandle AdjustmentHandle;
			AdjustmentHandle.EffectAdjustment = Adjustment;
			SourceActiveEffectAdjustmentContainer.Add(ActiveHandle, AdjustmentHandle);
		}
	}

	if(!GECDO->TargetGrantEffectAdjustments.IsEmpty())
	{
		for(UGameplayEffectAdjustment* Adjustment:GECDO->TargetGrantEffectAdjustments)
		{
			FActiveEffectAdjustmentHandle AdjustmentHandle;
			AdjustmentHandle.EffectAdjustment = Adjustment;
			TargetActiveEffectAdjustmentContainer.Add(ActiveHandle, AdjustmentHandle);
		}
	}
}

void URougeAbilitySystemComponent::HandleGameplayEffectRemovedFromSelf(const FActiveGameplayEffect& ActiveEffect)
{
	const FActiveGameplayEffectHandle& Handle = ActiveEffect.Handle;
	SourceActiveEffectAdjustmentContainer.Remove(Handle);
	TargetActiveEffectAdjustmentContainer.Remove(Handle);
}
