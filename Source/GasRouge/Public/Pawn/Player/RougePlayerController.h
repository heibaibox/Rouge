// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RougePlayerController.generated.h"

struct FInputActionValue;
class APawnBase;
/**
 * 
 */
UCLASS()
class GASROUGE_API ARougePlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	bool bIsTouch;

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<class ARougeHUD> HUD;
protected:

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	void Move(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<APawnBase> ControlPawn;

public:
	void OnHealthChanged(float Health);

	void OnMaxHealthChanged(float MaxHealth);
};
