// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CombatGameMode.h"
#include "RougeType.h"
#include "Kismet/GameplayStatics.h"
#include "PickUpActor/PickUpActor.h"
#include "Project/ProjectBase.h"
#include "UObject/UnrealTypePrivate.h"

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();

	ProjectilePool=TActorObjectPool<AProjectBase>(GetWorld(),InitCount,GrowCount);
	PickUpActorPool=TActorObjectPool<APickUpActor>(GetWorld(),InitCount,GrowCount);
}

AProjectBase* ACombatGameMode::SpawnProjectile(const TSharedPtr<FProjectileContext>& InProjectileContext)
{
	if(!InProjectileContext.IsValid())
	{
		return nullptr;
	}

	const FProjectileContext* ProjectileContextPtr=InProjectileContext.Get();
	if(!ProjectileContextPtr->ProjectileClass)
	{
		return nullptr;
	}

	UWorld* World=GetWorld();
	if(!World)
	{
		return nullptr;
	}
	if(!ProjectileSingle.Find(ProjectileContextPtr->ProjectileClass))
	{
		AProjectBase* Projectile=GetWorld()->SpawnActor<AProjectBase>(ProjectileContextPtr->ProjectileClass);
		ProjectileSingle.Add(ProjectileContextPtr->ProjectileClass,Projectile);
	}
	AProjectBase* NewProjectile = Cast<AProjectBase>(ProjectilePool.CreateActor());

	NewProjectile->Initialize(ProjectileSingle[ProjectileContextPtr->ProjectileClass],InProjectileContext);
	return NewProjectile;
}

APickUpActor* ACombatGameMode::SpawnPickUpActor(TSubclassOf<APickUpActor> PickUpActorClass,const FTransform& SpawnTransform)
{
	UWorld* World=GetWorld();
	if(!World)
	{
		return nullptr;
	}
	
	if(!PickUpActorSingle.Find(PickUpActorClass))
	{
		APickUpActor* Projectile=GetWorld()->SpawnActor<APickUpActor>(PickUpActorClass);
		PickUpActorSingle.Add(PickUpActorClass,Projectile);
	}

	APickUpActor* NewPickUpActor = Cast<APickUpActor>(PickUpActorPool.CreateActor());

	NewPickUpActor->Initialize(PickUpActorSingle[PickUpActorClass],SpawnTransform);
	return NewPickUpActor;
}

void ACombatGameMode::DestroyProjectile(AProjectBase* Projectile)
{
	ProjectilePool.DestoryActor(Projectile);
}

void ACombatGameMode::DestroyPickUpActor(APickUpActor* PickUpActor)
{
	PickUpActorPool.DestoryActor(PickUpActor);
}

void ACombatGameMode::AddEnemyToArray(AEnemyBase* Enemy)
{
	AllEnemyArray.Add(Enemy);
}

void ACombatGameMode::RemoveEnemeyForArray(AEnemyBase* Enemy)
{
	AllEnemyArray.Remove(Enemy);
}

void ACombatGameMode::GetAllEnemy(TArray<AEnemyBase*>& EnemyArray)
{
	for(auto Enemy:AllEnemyArray)
		EnemyArray.Add(Enemy);
}

