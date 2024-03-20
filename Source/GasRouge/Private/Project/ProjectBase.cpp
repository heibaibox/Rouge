// Fill out your copyright notice in the Description page of Project Settings.


#include "GasRouge/Public/Project/ProjectBase.h"

#include "AbilitySystemComponent.h"
#include "Component/RougeAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemGlobals.h"
#include "Components/SphereComponent.h"
#include "GameMode/CombatGameMode.h"
#include "GameAbility/GA/DamageGameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AProjectBase::AProjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);

	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	SetHidden(true);

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
	if(!bAlive)
		return;
	Super::Tick(DeltaTime);
	TickLifeTime(DeltaTime);
	TickMove(DeltaTime);
}

void AProjectBase::Initialize(const AProjectBase* _ProjectBase,const TSharedPtr<FProjectileContext>& _ProjectileContext)
{
	CurrLifeTime=0.f;
	bStartMove=false;
	ProjectileContext = _ProjectileContext;
	ProjectileBase=_ProjectBase->ProjectileBase;
	SphereComponent->SetSphereRadius(_ProjectBase->SphereComponent->GetScaledSphereRadius());
	StaticMeshComponent->SetStaticMesh(_ProjectBase->StaticMeshComponent->GetStaticMesh());
	StaticMeshComponent->SetRelativeTransform(_ProjectBase->StaticMeshComponent->GetRelativeTransform());
	SetActorTransform(ProjectileContext.Get()->SpawnTransform);
	bAlive=true;
}

void AProjectBase::TickLifeTime(float& DeltaTime)
{
	CurrLifeTime+=DeltaTime;
 	if(!ProjectileBase.bInfinityLifeTime)
 	{
 		if(CurrLifeTime>ProjectileBase.MaxLifeTime)
 		{
 			ProjectileEnd();
 		}
 	}
}

void AProjectBase::ProjectileEnd()
{
	bAlive=false;
	ACombatGameMode* CombatGameMode=Cast<ACombatGameMode>(GetWorld()->GetAuthGameMode());

	ProjectileContext.Reset();
	if(CombatGameMode)
	{
		CombatGameMode->DestroyProjectile(this);
	}
	else
	{
		Destroy();
	}
}


void AProjectBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bAlive)
		return;
	UAbilitySystemComponent* TargetAbilitySystem=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Other);
	if(TargetAbilitySystem)
	{
		if(!IsSameCamp(ProjectileContext.Get()->OwnerAbility.Get(),TargetAbilitySystem))
		{
			TryEffectArrayToTarget(TargetAbilitySystem,ProjectileBase.OverlopGameplayEffect);

			if(ProjectileContext!=nullptr&&ProjectileContext->GA)
			{
				if(UDamageGameplayAbility* DamageGameplayAbility=Cast<UDamageGameplayAbility>(ProjectileContext->GA))
				{
					DamageGameplayAbility->CauseDamage(Other,ProjectileBase.Damage);
				}
			}
			
			if(ProjectileBase.bCanPenetrate)
			{
				--ProjectileBase.MaxPenetrateCounts;
				if(ProjectileBase.MaxPenetrateCounts<0)
				{
					ProjectileEnd();
					return;
				}
				else
				{
					TryEffectArrayToTarget(TargetAbilitySystem,ProjectileBase.PenetrateGameplayEffect);
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
	if(!bAlive)
		return;
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
	if(CurrLifeTime<ProjectileBase.MoveDelay)
	{
		return;
	}
	StartMove();
	switch (ProjectileBase.MovementType)
	{
	case EMovementType::JustMoveForward:
		JustMoveForward(DeltaTime);
		break;
	}
}

void AProjectBase::JustMoveForward(float& DeltaTime)
{
	FVector NewLocation=GetActorLocation()+GetActorForwardVector()*ProjectileBase.Speed*DeltaTime;
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
			FGameplayEffectSpecHandle EffectSpecHandle=TargetAbilitySystem->MakeOutgoingSpec(Effective,ProjectileBase.Level,EffectContextHandle);
			OwnerAbility->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),TargetAbilitySystem);
		}
		
	}
}


void AProjectBase::LaunchCalculate(const AActor* OtherActor, const FHitResult& SweepResult)
{
	if(ProjectileBase.bCanLaunch)
    	{
    		if(!ProjectileBase.bCanInfinityLaunch)
    		{
    			--ProjectileBase.MaxLaunchCounts;
    			if(ProjectileBase.MaxLaunchCounts<0)
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

	if (!ProjectileContext.IsValid())
	{
		return;
	}
	const FProjectileContext* Context = ProjectileContext.Get();
	switch (ProjectileBase.MovementType)
	{
	case EMovementType::JustMoveForward:
		if (Context->TargetActor.IsValid())
		{
			FRotator DesiredRotation = (Context->TargetActor->GetActorLocation() - GetActorLocation()).ToOrientationRotator();
			DesiredRotation.Pitch = 0.f;
			SetActorRotation(DesiredRotation);
		}
		break;
	default:
		return;
	}
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

