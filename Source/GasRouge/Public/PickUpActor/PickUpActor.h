// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

class APlayerBase;
class UGameplayEffect;
UCLASS()
class GASROUGE_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bAlive=false;
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TWeakObjectPtr<APlayerBase> Target;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float MoveSpeed=20.f;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float Value;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FGameplayAttribute Attribute;

protected:
	void TryEffective(APlayerBase* Player);

	void PickUpActorEnd();
public:

	void Initialize(const APickUpActor* _PickUpActor,const FTransform& SpawnTransform);
	
	virtual void PickUp(APlayerBase* Player);

	void Attract(APlayerBase* Player);
};
