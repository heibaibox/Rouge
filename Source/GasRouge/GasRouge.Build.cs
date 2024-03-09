// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GasRouge : ModuleRules
{
	public GasRouge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput",
	        "Paper2D"
        });
        PrivateDependencyModuleNames.AddRange(new string[]{"GameplayAbilities", "GameplayTags", "GameplayTasks"});
	}
}
