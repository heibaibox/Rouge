// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor/PickUpActor.h"

#include "AbilitySystemComponent.h"
#include "GameAbility/GE/RougeGameplayEffect.h"
#include "GameMode/CombatGameMode.h"
#include "Pawn/Player/PlayerBase.h"

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bAlive)
		return;
	if(Target!=nullptr)
	{
		if(Target.IsValid())
		{
			FVector TargetLocation=Target.Get()->GetActorLocation();
			FVector SelfLocation=RootComponent->GetComponentLocation();
			FVector Differ=TargetLocation-SelfLocation;
			FVector Dir=FVector(Differ.X,Differ.Y,0);
			if(Dir.Length()>20.f)
			{
				Dir.Normalize();
				SetActorLocation(GetActorLocation()+Dir*MoveSpeed);
			}
			
		}
	}
}

void APickUpActor::TryEffective(APlayerBase* Player)
{
	UGameplayEffect* Effective=NewObject<UGameplayEffect>(URougeGameplayEffect::StaticClass());
	if(Effective)
	{
		Effective->DurationPolicy=EGameplayEffectDurationType::Instant;
		Effective->Modifiers.SetNum(1);
		FGameplayModifierInfo& ModifierInfo = Effective->Modifiers[0];
		ModifierInfo.Attribute=Attribute;
		ModifierInfo.ModifierOp = EGameplayModOp::Additive;
		ModifierInfo.ModifierMagnitude=FScalableFloat(Value);

		FGameplayEffectContext* Data=new FGameplayEffectContext;
		Data->AddInstigator(Player,Player);
		
		FGameplayEffectContextHandle DataHandle=FGameplayEffectContextHandle(Data);
		
		Player->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(Effective, 1.f,DataHandle);
	}
}

void APickUpActor::PickUpActorEnd()
{
	bAlive=false;
	Target=nullptr;
	ACombatGameMode* CombatGameMode=Cast<ACombatGameMode>(GetWorld()->GetAuthGameMode());
	
	if(CombatGameMode)
	{
		CombatGameMode->DestroyPickUpActor(this);
	}
	else
	{
		Destroy();
	}
}

void APickUpActor::Initialize(const APickUpActor* _PickUpActor,const FTransform& SpawnTransform)
{
	MoveSpeed=_PickUpActor->MoveSpeed;
	MeshComponent->SetStaticMesh(_PickUpActor->MeshComponent->GetStaticMesh());
	Value=_PickUpActor->Value;
	Attribute=_PickUpActor->Attribute;
	bAlive=true;
	SetActorTransform(SpawnTransform);
}

void APickUpActor::PickUp(APlayerBase* Player)
{
	if(!bAlive)
		return;
	TryEffective(Player);
	PickUpActorEnd();
}

void APickUpActor::Attract(APlayerBase* Player)
{
	Target=Player;
}

