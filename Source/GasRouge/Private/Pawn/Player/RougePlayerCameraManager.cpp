// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/RougePlayerCameraManager.h"

#include "Pawn/Player/RougePlayerController.h"

void ARougePlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController=Cast<ARougePlayerController>(GetOwningPlayerController());
	if(PlayerController.IsValid())
	{
		APawn* Pawn=PlayerController->GetPawn();
		if(Pawn)
		{
			SetViewTarget(Pawn);
		}
	}
}
