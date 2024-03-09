#pragma once

#include "CoreMinimal.h"

#include "RougeType.generated.h"

class URougeAbilitySystemComponent;
class AProjectBase;
class AActor;
class UBaseAttributeSet;
class URougeGameplayAbility;
struct FGameplayEffectSpec;

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
	TWeakObjectPtr<URougeGameplayAbility> GA;
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