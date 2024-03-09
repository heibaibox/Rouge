// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GA/RougeGameplayAbility.h"

#include "Pawn/PawnBase.h"

APawnBase* URougeGameplayAbility::GetOwnerPawn()
{
	if(CurrentActorInfo==nullptr)
		return nullptr;

	return Cast<APawnBase>(CurrentActorInfo->OwnerActor.Get());
}

APawnBase* URougeGameplayAbility::GetAvatarPawn()
{
	if(CurrentActorInfo==nullptr)
		return nullptr;

	return Cast<APawnBase>(CurrentActorInfo->AvatarActor.Get());
}
