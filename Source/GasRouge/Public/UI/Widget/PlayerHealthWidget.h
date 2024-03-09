// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASROUGE_API UPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void OnHealthChanged(float Health);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void OnMaxHealthChanged(float MaxHealth);
};
