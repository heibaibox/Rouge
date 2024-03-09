// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeType.h"
#include "GameFramework/Actor.h"
#include "ProjectBase.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UProjectileManagerComponent;
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

	void Initialize(UProjectileManagerComponent* _InOwner, const TSharedPtr<FProjectileContext>& _ProjectileContext);
private:

	float CurrLifeTime=0.f;
	
	bool bStartMove=false;

	TWeakObjectPtr<UProjectileManagerComponent> OwnerComponent;

	TSharedPtr<FProjectileContext> ProjectileContext;
protected:

	UPROPERTY(BlueprintReadWrite)
	float Level=1.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float Damage=1.f;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> OverlopGameplayEffect;
	//生命
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	bool bInfinityLifeTime=false;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase,meta=(EditCondition="!bInfinityLifeTime",EditConditionHides))
	float MaxLifeTime=5.f;
	
	//弹射
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	bool bCanLaunch=false;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase,meta=(EditCondition="bCanLaunch",EditConditionHides))
	bool bCanInfinityLaunch=false;
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase,meta=(EditCondition="!bCanInfinityLaunch",EditConditionHides))
	int32 MaxLaunchCounts=0;
	
	int32 CurrLaunchCounts=0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> LaunchGameplayEffect;
	//穿透
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	bool bCanPenetrate=false;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase,meta=(EditCondition="bCanPenetrate",EditConditionHides))
	int32 MaxPenetrateCounts=0;

	int32 CurrPenetrateCounts=0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> PenetrateGameplayEffect;
	//移动
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	float Speed=0.f;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	float MoveDelay=0.f;
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	EMovementType MovementType=EMovementType::JustMoveForward;

	
	
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

	void CauseDamage();
protected:

	bool IsSameCamp(UAbilitySystemComponent* A,UAbilitySystemComponent* B);
};
