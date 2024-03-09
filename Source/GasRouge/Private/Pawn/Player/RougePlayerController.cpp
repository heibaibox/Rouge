// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/RougePlayerController.h"

#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Pawn/PawnBase.h"
#include "UI/RougeHUD.h"

void ARougePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	ControlPawn=Cast<APawnBase>(GetPawn());
	HUD=Cast<ARougeHUD>(GetHUD());
}

void ARougePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARougePlayerController::Move);

	}
}

void ARougePlayerController::Move(const FInputActionValue& Value)
{
	if(ControlPawn.IsValid())
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		ControlPawn.Get()->Move(MovementVector);
	}
}

void ARougePlayerController::OnHealthChanged(float Health)
{
	HUD->OnHealthChanged(Health);
}

void ARougePlayerController::OnMaxHealthChanged(float MaxHealth)
{
	HUD->OnMaxHealthChanged(MaxHealth);
}
