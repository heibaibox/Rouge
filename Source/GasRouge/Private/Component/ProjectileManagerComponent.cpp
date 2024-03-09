// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Component\ProjectileManagerComponent.h"
#include "GasRouge/Public/Project/ProjectBase.h"
#include "RougeType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UProjectileManagerComponent::UProjectileManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProjectileManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AProjectBase* UProjectileManagerComponent::SpawnProjectile(const TSharedPtr<FProjectileContext>& InProjectileContext)
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
	AProjectBase* NewProjectile = Cast<AProjectBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this,ProjectileContextPtr->ProjectileClass, ProjectileContextPtr->SpawnTransform));
	
	NewProjectile->Initialize(this,InProjectileContext);

	UGameplayStatics::FinishSpawningActor(NewProjectile, ProjectileContextPtr->SpawnTransform);
	return NewProjectile;
}

