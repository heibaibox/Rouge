// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Enemy/EnemyBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbility.h"
#include "Component/RougeAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "FunctionLibrary/RougeFunctionLibrary.h"
#include "GameAbility/AttributeSet/HealthAttributeSet.h"
#include "GameMode/CombatGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pawn/Player/PlayerBase.h"

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(AttackTarget.IsValid()&&DamageAbilityClass)
	{
		RougeAbilitySystemComponent->TryActivateAbilityByClass(DamageAbilityClass,true);
	}
}

void AEnemyBase::SetTarget(APlayerBase* _Target)
{
	Target=_Target;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	RegisterCollision(Cast<UPrimitiveComponent>(GetRootComponent()));

	Initialize();
	GetRougeAbilitySystemComponent()->Camp=EPawnCamp::Enemy;
	
	URougeFunctionLibrary::GetCombatGameMode(GetWorld())->AddEnemyToArray(this);

	if(RougeAbilitySystemComponent)
	{
		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::GetHealthAttribute())
		.AddUObject(this, &AEnemyBase::OnHealthAttributeChanged);
	}
}

void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	URougeFunctionLibrary::GetCombatGameMode(GetWorld())->RemoveEnemeyForArray(this);
}

void AEnemyBase::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	UKismetSystemLibrary::PrintString(GetWorld(),"Hit");
}

void AEnemyBase::RegisterCollision(UPrimitiveComponent* InComponent)
{
	if(!InComponent)
		return;

	InComponent->OnComponentBeginOverlap.AddDynamic(this,&AEnemyBase::OnBeginOverlap);
	InComponent->OnComponentEndOverlap.AddDynamic(this,&AEnemyBase::OnEndOverlap);
}

void AEnemyBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APlayerBase* Player=Cast<APlayerBase>(Other))
	{
		AttackTarget=Player;
	}
}

void AEnemyBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(APlayerBase* Player=Cast<APlayerBase>(OtherActor))
	{
		AttackTarget=nullptr;
	}
}

void AEnemyBase::CauseDamage()
{
	const URougeAbilitySystemComponent* AbilitySystemComponent=AttackTarget->GetRougeAbilitySystemComponent();
	if(AbilitySystemComponent)
	{
		
	}
}
