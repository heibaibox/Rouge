// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/Enemy/EnemyBase.h"
#include "EasyEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class GASROUGE_API AEasyEnemyBase : public AEnemyBase
{
	GENERATED_BODY()

public:

	AEasyEnemyBase();
	
	virtual void Tick(float DeltaSeconds) override;
};
