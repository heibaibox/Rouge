#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FRougeGameplayTags
{
public:
	static const FRougeGameplayTags& Get() { return GameplayTags; };
	static void InitializeXiuXianGameplayTags();

	FGameplayTag Damage;
private:
	static FRougeGameplayTags GameplayTags;
};
