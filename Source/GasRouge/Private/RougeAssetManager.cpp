// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAssetManager.h"

#include "RougeGameplayTags.h"

URougeAssetManager& URougeAssetManager::Get()
{
	check(GEngine);
	
	URougeAssetManager* XXAssetManager = Cast<URougeAssetManager>(GEngine->AssetManager);
	return *XXAssetManager;
}

void URougeAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FRougeGameplayTags::InitializeXiuXianGameplayTags();
}
