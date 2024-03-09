// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnBase.h"
#include "GasRouge/Public/Component/RougeAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameAbility/AttributeSet/BaseAttributeSet.h"
#include "Component/ProjectileManagerComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnMovement=CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	ProjectileManagerComponent=CreateDefaultSubobject<UProjectileManagerComponent>(TEXT("ProjectileManagerComponent"));
	RougeAbilitySystemComponent=CreateDefaultSubobject<URougeAbilitySystemComponent>(TEXT("RougeAbilitySystemComponent"));

	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	Sprite=CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	if (Sprite)
	{
		Sprite->AlwaysLoadOnClient = true;
		Sprite->AlwaysLoadOnServer = true;
		Sprite->bOwnerNoSee = false;
		Sprite->bAffectDynamicIndirectLighting = true;
		Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Sprite->SetupAttachment(GetRootComponent());
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		Sprite->SetCollisionProfileName(CollisionProfileName);
		Sprite->SetGenerateOverlapEvents(false);
		Sprite->SetWorldRotation(FRotator(0,90,-90));
	}
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Velocity=PawnMovement->Velocity;
	if(Velocity.Length()>0)
	{
		if(MovementState==EPawnMovementState::Idle&&RunFlipbook)
		{
			MovementState=EPawnMovementState::Run;
			Sprite->SetFlipbook(RunFlipbook);
		}
	}
	else
	{
		if(MovementState==EPawnMovementState::Run&&IdleFlipbook)
		{
			MovementState=EPawnMovementState::Idle;
			Sprite->SetFlipbook(IdleFlipbook);
		}
	}
}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnBase::Initialize()
{
	const UBaseAttributeSet* BaseAttributeSet = Cast<UBaseAttributeSet>(RougeAbilitySystemComponent->GetAttributeSet(UBaseAttributeSet::StaticClass()));
	if(BaseAttributeSet)
	{
		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetSpeedAttribute()).
		AddLambda([&](const FOnAttributeChangeData& Data)->void{this->Speed=Data.NewValue;});
		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxSpeedAttribute()).
		AddLambda([&](const FOnAttributeChangeData& Data)->void{this->PawnMovement->MaxSpeed=Data.NewValue;});
	}
}

UAbilitySystemComponent* APawnBase::GetAbilitySystemComponent() const
{
	UAbilitySystemComponent* AbilitySystemComponent=Cast<UAbilitySystemComponent>(RougeAbilitySystemComponent);
	return AbilitySystemComponent;
}

URougeAbilitySystemComponent* APawnBase::GetRougeAbilitySystemComponent()
{
	return RougeAbilitySystemComponent;
}

void APawnBase::Move(FVector2D& Direction)
{
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Direction.Y*Speed);
		AddMovementInput(RightDirection, Direction.X*Speed);

		Rotate(Direction);
	}
}

void APawnBase::Rotate(FVector2D& Direction)
{
	if(Direction.X>0)
	{
		Sprite->SetWorldRotation(FRotator(0,90,-90));
	}
	else if(Direction.X<0)
	{
		Sprite->SetWorldRotation(FRotator(180,90,-90));
	}
	
}

void APawnBase::GiveAbility(TSubclassOf<UGameplayAbility> Ability, int32 Level)
{
	if (RougeAbilitySystemComponent)
	{
		if (HasAuthority() && Ability)
		{
			RougeAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, Level));
		}
		RougeAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
