// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/PlayerBase.h"

#include "Component/RougeAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameAbility/AttributeSet/HealthAttributeSet.h"
#include "Pawn/Player/RougePlayerController.h"


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

void APlayerBase::BindAttributeDelegate()
{
	if(RougeAbilitySystemComponent)
	{
		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::GetHealthAttribute())
		.AddUObject(this, &APlayerBase::OnHealthAttributeChanged);

		RougeAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UHealthAttributeSet::GetMaxHealthAttribute())
		.AddUObject(this, &APlayerBase::OnMaxHealthAttributeChanged);
	}
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	RougeController=Cast<ARougePlayerController>(GetController());
	BindAttributeDelegate();

}

void APlayerBase::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	/*Super::CalcCamera(DeltaTime, OutResult);*/
	OutResult.Location = GetActorLocation() + CameraOffset;
	OutResult.Rotation = (GetActorLocation() - OutResult.Location).ToOrientationRotator();


	
}
