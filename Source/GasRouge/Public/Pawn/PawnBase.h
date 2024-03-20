// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Pawn.h"
#include "GameplayEffectTypes.h"
#include "RougeType.h"
#include "PawnBase.generated.h"

class URougeAbilitySystemComponent;
class UAbilitySystemComponent;
class UFloatingPawnMovement;
class UPaperFlipbook;

UCLASS()
class GASROUGE_API APawnBase : public APawn,public IAbilitySystemInterface
{
	GENERATED_BODY()

	// Name of the Sprite component
	static FName SpriteComponentName;
	
public:
	// Sets default values for this pawn's properties
	APawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPaperFlipbookComponent> Sprite;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	float Speed=1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* PawnMovement;

	UPROPERTY(Category = Flipbook, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* IdleFlipbook;

	UPROPERTY(Category = Flipbook, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* RunFlipbook;

	EPawnMovementState MovementState=EPawnMovementState::Idle;

protected:

	virtual void Initialize();

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Abilities)
	URougeAbilitySystemComponent* RougeAbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	URougeAbilitySystemComponent* GetRougeAbilitySystemComponent();

	void Move(FVector2D& Direction);

	void Rotate(FVector2D& Direction);

	//添加Ability
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void GiveAbility(TSubclassOf<UGameplayAbility> Ability, int32 Level = 1);
};
