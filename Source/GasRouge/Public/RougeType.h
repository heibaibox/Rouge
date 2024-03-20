#pragma once

#include "CoreMinimal.h"
#include "GameAbility/GA/RougeGameplayAbility.h"

#include "RougeType.generated.h"

class URougeAbilitySystemComponent;
class AProjectBase;
class AActor;
class UBaseAttributeSet;
class URougeGameplayAbility;
struct FGameplayEffectSpec;
class UGameplayEffect;
class UGameplayEffectAdjustment;

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	JustMoveForward
};

USTRUCT(BlueprintType)
struct FProjectileContext
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AProjectBase> ProjectileClass;

	UPROPERTY(BlueprintReadWrite)
	FTransform SpawnTransform;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<URougeAbilitySystemComponent> OwnerAbility;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AActor> TargetActor;

	UPROPERTY(BlueprintReadOnly)
	URougeGameplayAbility* GA;
	
};

USTRUCT(BlueprintType)
struct FProjectileBaseSet
{
	GENERATED_BODY()

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
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> LaunchGameplayEffect;
	//穿透
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	bool bCanPenetrate=false;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase,meta=(EditCondition="bCanPenetrate",EditConditionHides))
	int32 MaxPenetrateCounts=0;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> PenetrateGameplayEffect;
	//移动
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	float Speed=0.f;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	float MoveDelay=0.f;
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category=ProjectBase)
	EMovementType MovementType=EMovementType::JustMoveForward;

};
UENUM(BlueprintType)
enum class EPawnMovementState : uint8
{
	Idle,
	Run
};

UENUM(BlueprintType)
enum class EPawnCamp : uint8
{
	Player,
	Enemy,
	Neutrality
};

UENUM(BlueprintType)
enum class EItemType: uint8
{
	Weapon,
	Corselet,
	Boot,
	Consumables
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	EItemType ItemType;
	
	int32 Length=1;

	int32 Width=1;
};

USTRUCT(BlueprintType)
struct FExperienceTable:public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 Experience;
};

USTRUCT(BlueprintType)
struct FActiveEffectAdjustmentHandle
{
	GENERATED_BODY()

   UPROPERTY()
	TObjectPtr<UGameplayEffectAdjustment> EffectAdjustment;
	
};

USTRUCT(BlueprintType)
struct FGameplayEffectAdjustmentData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float ExtraValue=0.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float RateValue=1.f;

	FGameplayEffectAdjustmentData& operator=(FGameplayEffectAdjustmentData& AdjustmentData)
	{
		ExtraValue=AdjustmentData.ExtraValue;
		RateValue=AdjustmentData.RateValue;
		return *this;
	}
};

USTRUCT(BlueprintType)
struct FRougeExcutionHelper
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<URougeAbilitySystemComponent> SourceASC=nullptr;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<URougeAbilitySystemComponent> TargetASC=nullptr;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<const UBaseAttributeSet> SourceAS=nullptr;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<const UBaseAttributeSet> TargetAS=nullptr;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<const URougeGameplayAbility> SourceGA=nullptr;

	FGameplayEffectSpec* Spec=nullptr;

	FGameplayEffectAdjustmentData AdjustmentData;
};