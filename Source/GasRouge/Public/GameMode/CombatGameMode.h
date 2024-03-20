// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ObjectPool/ObjectPool.h"
#include "CombatGameMode.generated.h"

class AProjectBase;
class AEnemyBase;
struct FProjectileContext;
class APickUpActor;
/**
 * 
 */
UCLASS()
class GASROUGE_API ACombatGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintReadOnly,EditAnywhere,meta=(AllowPrivateAccess))
	int32 InitCount=0;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,meta=(AllowPrivateAccess))
	int32 GrowCount=0;
	
	TActorObjectPool<AProjectBase> ProjectilePool;
	
	TMap<TSubclassOf<AProjectBase>,AProjectBase*> ProjectileSingle;
	
	TActorObjectPool<APickUpActor> PickUpActorPool;
	
	TMap<TSubclassOf<APickUpActor>,APickUpActor*> PickUpActorSingle;

	TArray<AEnemyBase*> AllEnemyArray;
	
protected:

	virtual void BeginPlay() override;
public:
	AProjectBase* SpawnProjectile(const TSharedPtr<FProjectileContext>& InProjectileContext);

	APickUpActor* SpawnPickUpActor(TSubclassOf<APickUpActor> PickUpActorClass,const FTransform& SpawnTransform);
	
	void DestroyProjectile(AProjectBase* Projectile);

	void DestroyPickUpActor(APickUpActor* PickUpActor);

	void AddEnemyToArray(AEnemyBase* Enemy);

	void RemoveEnemeyForArray(AEnemyBase* Enemy);

	void GetAllEnemy(TArray<AEnemyBase*>& EnemyArray); 
};
