// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/RougeFunctionLibrary.h"

#include "RougeType.h"
#include "Component/RougeAbilitySystemComponent.h"
#include "GameMode/CombatGameMode.h"
#include "Pawn/PawnBase.h"
#include "Pawn/Enemy/EnemyBase.h"
#include "GameAbility/GA/RougeGameplayAbility.h"
#include "GameAbility/GE/RougeGameplayEffect.h"
#include "Kismet/GameplayStatics.h"
#include "PickUpActor/PickUpActor.h"
#include "Project/ProjectBase.h"

AProjectBase* URougeFunctionLibrary::CreateNewProjectile(AGameModeBase* GameModeBase,TSubclassOf<AProjectBase> ProjectileClass,
                                                         const FTransform& SpawnTransform, AActor* TargetActor,
                                                         URougeAbilitySystemComponent* AbilityComponent,
                                                         URougeGameplayAbility* GA)
{
	if(!AbilityComponent)
	{
		
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

	if (GA != nullptr)
	{
		ProjectileContext->GA=GA;
	}
	ProjectileContext->SpawnTransform = SpawnTransform;
	ProjectileContext->OwnerAbility=AbilityComponent;
	ProjectileContext->ProjectileClass=ProjectileClass;
	ProjectileContext->TargetActor=TargetActor;
	

	const TSharedPtr<FProjectileContext> ProjectileContextSharePtr = TSharedPtr<FProjectileContext>(ProjectileContext);
	
	ACombatGameMode* CombatGameMode=Cast<ACombatGameMode>(GameModeBase);

	if(CombatGameMode)
	{
		AProjectBase* Projectile=CombatGameMode->SpawnProjectile(ProjectileContextSharePtr);
		return Projectile;
	}
	return nullptr;
	
}

APickUpActor* URougeFunctionLibrary::CreateNewPickUpActor(AGameModeBase* GameModeBase,
	TSubclassOf<APickUpActor> PickUpActorClass, const FTransform& SpawnTransform)
{
	if(!PickUpActorClass)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateNewPickUpActor Failed, Invalid PickUpActor Class"))
		return nullptr;
	}

	ACombatGameMode* CombatGameMode=Cast<ACombatGameMode>(GameModeBase);
	if(CombatGameMode)
	{
		APickUpActor* PickUpActor=CombatGameMode->SpawnPickUpActor(PickUpActorClass,SpawnTransform);
		return PickUpActor;
	}
	return nullptr;
}

//TODO:完善
bool URougeFunctionLibrary::GetClosestEnemies(const AActor* InActor, TArray<AEnemyBase*>& OutEnemies, int32 MaxNum)
{
	if(MaxNum<1)
		return false;
	if(InActor==nullptr)
		return false;

	TArray<AEnemyBase*> AllEnemies;
	GetCombatGameMode(InActor)->GetAllEnemy(AllEnemies);

	if (AllEnemies.Num() == 0)
	{
		return false;
	}
	if (AllEnemies.Num() <= MaxNum)
	{
		// Return All
		OutEnemies.Append(AllEnemies);
		return true;
	}
	const FVector CharacterLocation = InActor->GetActorLocation();
	AllEnemies.Sort([&CharacterLocation](const AEnemyBase& A, const AEnemyBase& B) {
			const float SizeSquared2D_A = (CharacterLocation - A.GetActorLocation()).SizeSquared2D();
			const float SizeSquared2D_B = (CharacterLocation - B.GetActorLocation()).SizeSquared2D();
			return SizeSquared2D_A < SizeSquared2D_B;
		});
	for (int32 i = 0; i < MaxNum; i++)
	{
		OutEnemies.Add(AllEnemies[i]);
	}
	return true;
}

ACombatGameMode* URougeFunctionLibrary::GetCombatGameMode(const UObject* WorldContext)
{
	if(WorldContext == nullptr || WorldContext->GetWorld() == nullptr)
		return nullptr;
	return Cast<ACombatGameMode>(WorldContext->GetWorld()->GetAuthGameMode());
}
