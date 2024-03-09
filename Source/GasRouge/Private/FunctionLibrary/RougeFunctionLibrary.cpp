// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/RougeFunctionLibrary.h"

#include "RougeType.h"
#include "Component/ProjectileManagerComponent.h"
#include "Component/RougeAbilitySystemComponent.h"
#include "Pawn/PawnBase.h"
#include "GameAbility/GA/RougeGameplayAbility.h"
#include "Project/ProjectBase.h"

AProjectBase* URougeFunctionLibrary::CreateNewProjectile(TSubclassOf<AProjectBase> ProjectileClass,
                                                         const FTransform& SpawnTransform, AActor* TargetActor,
                                                         URougeAbilitySystemComponent* AbilityComponent,
                                                         URougeGameplayAbility* GA)
{
	if(!AbilityComponent)
	{
		UE_LOG(LogTemp,Warning,TEXT("CreateNewProjectile Failed, Invalid AbilityComponent"));
		return nullptr;
	}

	APawnBase* PawnBase=Cast<APawnBase>(AbilityComponent->GetOwner());
	
	if(!PawnBase)
		return nullptr;

	FProjectileContext* ProjectileContext = new FProjectileContext();
	
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateNewProjectile Failed, Invalid Porjectile Class"))
		return nullptr;
	}

	ProjectileContext->SpawnTransform = SpawnTransform;
	ProjectileContext->OwnerAbility=AbilityComponent;
	ProjectileContext->ProjectileClass=ProjectileClass;
	ProjectileContext->TargetActor=TargetActor;
	ProjectileContext->GA=GA;

	const TSharedPtr<FProjectileContext> ProjectileContextSharePtr = TSharedPtr<FProjectileContext>(ProjectileContext);
	return PawnBase->GetProjectileManagerComponent()->SpawnProjectile(ProjectileContextSharePtr);
	
}
