// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeType.h"

#include "GameFramework/Actor.h"
#include "ObjectPool/ObjectPool.h"
#include "ProjectBase.generated.h"

class USphereComponent;
class UAbilitySystemComponent;
class UGameplayEffect;
UCLASS()
class GASROUGE_API AProjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(const AProjectBase* _ProjectBase,const TSharedPtr<FProjectileContext>& _ProjectileContext);
private:

	float CurrLifeTime=0.f;
	
	bool bStartMove=false;

	TSharedPtr<FProjectileContext> ProjectileContext;

	bool bAlive=false;
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FProjectileBaseSet ProjectileBase;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
private:

	void TickLifeTime(float& DeltaTime);

	//子弹生命周期结束
	void ProjectileEnd();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void RegisterCollision(UPrimitiveComponent* InComponent);

	void TickMove(float& DeltaTime);
	
	void JustMoveForward(float& DeltaTime);

	//对目标执行Effective数组
	void TryEffectArrayToTarget(UAbilitySystemComponent* TargetAbilitySystem,TArray<TSubclassOf<UGameplayEffect>>& EffectArray);

	//计算反弹
	void LaunchCalculate(const AActor* OtherActor, const FHitResult& SweepResult);

	//进行反弹时的Effective
	void TryLaunchEffect();

	void StartMove();

protected:

	bool IsSameCamp(UAbilitySystemComponent* A,UAbilitySystemComponent* B);

public:
	FProjectileBaseSet GetProjectileBaseSet(){return ProjectileBase;}
};
