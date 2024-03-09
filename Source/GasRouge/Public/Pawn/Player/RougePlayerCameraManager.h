// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "RougePlayerCameraManager.generated.h"

/**
 * 
 */

class ARougePlayerController;

UCLASS()
class GASROUGE_API ARougePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<ARougePlayerController> PlayerController;
};
