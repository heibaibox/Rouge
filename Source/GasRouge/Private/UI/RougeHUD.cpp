// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RougeHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/PlayerHealthWidget.h"

void ARougeHUD::BeginPlay()
{
	Super::BeginPlay();

	if(PlayerHealthWidgetClass!=nullptr)
	{
		PlayerHealthWidget=CreateWidget<UPlayerHealthWidget>(GetWorld(),PlayerHealthWidgetClass);
		PlayerHealthWidget->AddToViewport();
	}
		
}

void ARougeHUD::OnHealthChanged(float Health)
{
}

void ARougeHUD::OnMaxHealthChanged(float MaxHealth)
{
}
