// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Survival : ModuleRules
{
	public Survival(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"GradessGASLibrary",
			"GradessLibraryRuntime",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
		
		if (Target.bBuildDeveloperTools || (Target.Configuration != UnrealTargetConfiguration.Shipping && Target.Configuration != UnrealTargetConfiguration.Test))
		{
			PrivateDependencyModuleNames.Add("GameplayDebugger");
			PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=1");
		}
		else
		{
			PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=0");
		}
	}
}
