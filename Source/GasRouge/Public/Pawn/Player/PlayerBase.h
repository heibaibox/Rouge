// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PawnBase.h"
#include "PlayerBase.generated.h"

class USphereComponent;
class ARougePlayerController;
class AEnemyBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeEvent, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChangeEvent, float, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeEvent, float, NewMaxHealth);
/**
 * 
 */
UCLASS()
class GASROUGE_API APlayerBase : public APawnBase
{
	GENERATED_BODY()

public:

	APlayerBase();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector CameraOffset = FVector(-400.f, 0.f, 1000.f);

protected:

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnHealthChangeEvent HealthChangeEvent;

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnMaxHealthChangeEvent MaxHealthChangeEvent;

	UPROPERTY(BlueprintAssignable,Category="Ability")
	FOnLevelChangeEvent LevelChangeEvent;
	
	UPROPERTY(BlueprintReadOnly)
	ARougePlayerController* RougeController;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* PickUpSphere;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* AttractSphere;
private:

	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
    
	void OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data);

	void OnLevelChangeEvent(const FOnAttributeChangeData& Data);

	void BindAttributeDelegate();

protected:

	virtual void Initialize() override;

	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPickUpBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnAttractBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
};
