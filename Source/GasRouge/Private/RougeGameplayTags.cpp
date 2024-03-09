#include "RougeGameplayTags.h"

#include "GameplayTagsManager.h"

FRougeGameplayTags FRougeGameplayTags::GameplayTags;
void FRougeGameplayTags::InitializeXiuXianGameplayTags()
{
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSystem.Damage"),
		FString("Damage")
		);
}
