// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RougeAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GASROUGE_API URougeAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static URougeAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
