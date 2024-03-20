// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/PlayerBase.h"

#include "Component/RougeAbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameAbility/AttributeSet/ExperienceAttributeSet.h"
#include "GameAbility/AttributeSet/HealthAttributeSet.h"
#include "Pawn/Enemy/EnemyBase.h"
#include "Pawn/Player/RougePlayerController.h"
#include "PickUpActor/PickUpActor.h"


APlayerBase::APlayerBase()
{
	PickUpSphere=CreateDefaultSubobject<USphereComponent>(TEXT("PickUpSphere"));
	PickUpSphere->SetupAttachment(RootComponent);

	AttractSphere=CreateDefaultSubobject<USphereComponent>(TEXT("AttributeSphere"));
	AttractSphere->SetupAttachment(RootComponent);
}

void APlayerBase::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	if(RougeController)
	{
		RougeController->OnHealthChanged(Data.NewValue);
	}
	
}

void APlayerBase::OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	if(RougeController)
	{
		RougeController->OnMaxHealthChanged(Data.NewValue);
	}
}

void APlayerBase::OnLevelChangeEvent(const FOnAttributeChangeData& Data)
{
}

void APlayerBase::BindAttributeDelegate()
{
	if(RougeAbilitySystemComponent)
	{
		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::GetHealthAttribute())
		.AddUObject(this, &APlayerBase::OnHealthAttributeChanged);

		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::GetMaxHealthAttribute())
		.AddUObject(this, &APlayerBase::OnMaxHealthAttributeChanged);

		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UExperienceAttributeSet::GetLevelAttribute())
		.AddUObject(this,&APlayerBase::OnLevelChangeEvent);
	}
}

void APlayerBase::Initialize()
{
	Super::Initialize();
	BindAttributeDelegate();
}


void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	RougeController=Cast<ARougePlayerController>(GetController());
	Initialize();

	if(const UHealthAttributeSet* HealthAS=Cast<UHealthAttributeSet>(RougeAbilitySystemComponent->GetAttributeSet(UHealthAttributeSet::StaticClass())))
	{
		RougeController->OnMaxHealthChanged(HealthAS->GetMaxHealth());
		RougeController->OnHealthChanged(HealthAS->GetHealth());
		
	}

	PickUpSphere->OnComponentBeginOverlap.AddDynamic(this,&APlayerBase::OnPickUpBeginOverlap);
	AttractSphere->OnComponentBeginOverlap.AddDynamic(this,&APlayerBase::OnAttractBeginOverlap);
}

void APlayerBase::OnPickUpBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Other)
	{
		APickUpActor* PickUpActor=Cast<APickUpActor>(Other);
		if(PickUpActor)
		{
			PickUpActor->PickUp(this);
		}
	}
}

void APlayerBase::OnAttractBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Other)
	{
		APickUpActor* PickUpActor=Cast<APickUpActor>(Other);
		if(PickUpActor)
		{
			PickUpActor->Attract(this);
		}
	}
}

void APlayerBase::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	/*Super::CalcCamera(DeltaTime, OutResult);*/
	OutResult.Location = GetActorLocation() + CameraOffset;
	OutResult.Rotation = (GetActorLocation() - OutResult.Location).ToOrientationRotator();
	
}
