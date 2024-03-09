// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RougeHUD.generated.h"

class UPlayerHealthWidget;
class UUserWidget;
/**
 * 
 */
UCLASS()
class GASROUGE_API ARougeHUD : public AHUD
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerHealthWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UPlayerHealthWidget* PlayerHealthWidget;

protected:
	virtual void BeginPlay() override;
	
public:
	void OnHealthChanged(float Health);

	void OnMaxHealthChanged(float MaxHealth);
};
