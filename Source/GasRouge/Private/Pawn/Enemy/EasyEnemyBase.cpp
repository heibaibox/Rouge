// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Enemy/EasyEnemyBase.h"

#include "Pawn/Player/PlayerBase.h"

AEasyEnemyBase::AEasyEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEasyEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Target.IsValid())
	{
		FVector TargetLocation=Target.Get()->GetActorLocation();
		FVector SelfLocation=RootComponent->GetComponentLocation();
		FVector Differ=TargetLocation-SelfLocation;
		FVector2D Dir=FVector2D(Differ.Y,Differ.X);
		Dir.Normalize();
		Move(Dir);
	}
}
