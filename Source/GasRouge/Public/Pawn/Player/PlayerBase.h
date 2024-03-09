// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PawnBase.h"
#include "PlayerBase.generated.h"

class UCapsuleComponent;
class ARougePlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeEvent, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeEvent, float, NewHealth);
/**
 * 
 */
UCLASS()
class GASROUGE_API APlayerBase : public APawnBase
{
	GENERATED_BODY()

public:

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector CameraOffset = FVector(-400.f, 0.f, 1000.f);

protected:

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnHealthChangeEvent HealthChangeEvent;

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnMaxHealthChangeEvent MaxHealthChangeEvent;
	
	UPROPERTY(BlueprintReadOnly)
	ARougePlayerController* RougeController;

private:

	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
    
	void OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data);

	void BindAttributeDelegate();
protected:


	
	virtual void BeginPlay() override;
public:
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
};
