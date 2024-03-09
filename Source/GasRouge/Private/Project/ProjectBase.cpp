// Fill out your copyright notice in the Description page of Project Settings.


#include "GasRouge/Public/Project/ProjectBase.h"

#include "AbilitySystemComponent.h"
#include "Component/RougeAbilitySystemComponent.h"
#include "Component/ProjectileManagerComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemGlobals.h"
#include "GameAbility/GA/DamageGameplayAbility.h"
#include "Pawn/PawnBase.h"

// Sets default values
AProjectBase::AProjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectBase::BeginPlay()
{
	Super::BeginPlay();

	RegisterCollision(Cast<UPrimitiveComponent>(GetRootComponent()));
}

// Called every frame
void AProjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickLifeTime(DeltaTime);
	TickMove(DeltaTime);
}

void AProjectBase::Initialize(UProjectileManagerComponent* _Owner, const TSharedPtr<FProjectileContext>& _ProjectileContext)
{
	CurrLifeTime=0.f;
	bStartMove=false;
	OwnerComponent = _Owner;
	ProjectileContext = _ProjectileContext;
	CurrLaunchCounts=MaxLaunchCounts;
	CurrPenetrateCounts=MaxPenetrateCounts;
}

void AProjectBase::TickLifeTime(float& DeltaTime)
{
	CurrLifeTime+=DeltaTime;
 	if(!bInfinityLifeTime)
 	{
 		if(CurrLifeTime>MaxLifeTime)
 		{
 			Destroy();
 		}
 	}
}

void AProjectBase::ProjectileEnd()
{
	Destroy();
}


void AProjectBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UAbilitySystemComponent* TargetAbilitySystem=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Other);
	if(TargetAbilitySystem)
	{
		if(!IsSameCamp(ProjectileContext.Get()->OwnerAbility.Get(),TargetAbilitySystem))
		{
			TryEffectArrayToTarget(TargetAbilitySystem,OverlopGameplayEffect);

			if(ProjectileContext!=nullptr&&ProjectileContext->GA.IsValid())
			{
				if(UDamageGameplayAbility* DamageGameplayAbility=Cast<UDamageGameplayAbility>(ProjectileContext->GA.Get()))
				{
					DamageGameplayAbility->CauseDamage(Other,Damage);
				}
			}
			
			if(bCanPenetrate)
			{
				--CurrPenetrateCounts;
				if(CurrPenetrateCounts<0)
				{
					ProjectileEnd();
					return;
				}
				else
				{
					TryEffectArrayToTarget(TargetAbilitySystem,PenetrateGameplayEffect);
				}
			}
		}
	}
	else if(bFromSweep)
	{
		LaunchCalculate(Other,SweepResult);
	}
	
}

void AProjectBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AProjectBase::RegisterCollision(UPrimitiveComponent* InComponent)
{
	if(!InComponent)
	{
		return;
	}

	InComponent->OnComponentBeginOverlap.AddDynamic(this,&AProjectBase::OnBeginOverlap);
	InComponent->OnComponentEndOverlap.AddDynamic(this,&AProjectBase::OnEndOverlap);
}

void AProjectBase::TickMove(float& DeltaTime)
{
	if(CurrLifeTime<MoveDelay)
	{
		return;
	}
	StartMove();
	switch (MovementType)
	{
	case EMovementType::JustMoveForward:
		JustMoveForward(DeltaTime);
		break;
	}
}

void AProjectBase::JustMoveForward(float& DeltaTime)
{
	FVector NewLocation=GetActorLocation()+GetActorForwardVector()*Speed*DeltaTime;
	SetActorLocation(NewLocation,true);
}

void AProjectBase::TryEffectArrayToTarget(UAbilitySystemComponent* TargetAbilitySystem,TArray<TSubclassOf<UGameplayEffect>>& EffectArray)
{
	for(auto Effective:EffectArray)
	{
		if(Effective!=nullptr)
		{
			FGameplayEffectContextHandle EffectContextHandle=TargetAbilitySystem->MakeEffectContext();
			UAbilitySystemComponent* OwnerAbility=ProjectileContext->OwnerAbility.Get();
			EffectContextHandle.AddSourceObject(OwnerAbility);
			FGameplayEffectSpecHandle EffectSpecHandle=TargetAbilitySystem->MakeOutgoingSpec(Effective,Level,EffectContextHandle);
			OwnerAbility->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),TargetAbilitySystem);
		}
		
	}
}


void AProjectBase::LaunchCalculate(const AActor* OtherActor, const FHitResult& SweepResult)
{
	if(bCanLaunch)
    	{
    		if(!bCanInfinityLaunch)
    		{
    			--CurrLaunchCounts;
    			if(CurrLaunchCounts<0)
    			{
    				ProjectileEnd();
    				return;
    			}
    		}
    		const FVector ForwardVector=GetActorForwardVector();
    		const FVector NormalVector=SweepResult.ImpactNormal;
    		const FVector LaunchVector=ForwardVector-2*(ForwardVector|NormalVector)*NormalVector;
			SetActorRotation(LaunchVector.ToOrientationRotator());
    	}
}

void AProjectBase::TryLaunchEffect()
{
	
}

void AProjectBase::StartMove()
{
	if(bStartMove)
	{
		return;
	}
	bStartMove=true;

	
}

bool AProjectBase::IsSameCamp(UAbilitySystemComponent* A, UAbilitySystemComponent* B)
{
	if(A&&B)
	{
		URougeAbilitySystemComponent* PawnA=Cast<URougeAbilitySystemComponent>(A);
		URougeAbilitySystemComponent* PawnB=Cast<URougeAbilitySystemComponent>(B);
		if(PawnA&&PawnB&&PawnA->Camp==PawnB->Camp)
			return true;
		
	}
	return false;
}

