// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PawnBase.h"
#include "EnemyBase.generated.h"

class APlayerBase;
class UDamageGameplayAbility;
class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class GASROUGE_API AEnemyBase : public APawnBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TWeakObjectPtr<APlayerBase> Target;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="GameplayAbility")
	TSubclassOf<UGameplayAbility> DamageAbilityClass;
private:
	TWeakObjectPtr<APlayerBase> AttackTarget;
public:
	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(APlayerBase* _Target);

	
protected:
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	
	UFUNCTION(BlueprintCallable)
	void RegisterCollision(UPrimitiveComponent* InComponent);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CauseDamage();
};
