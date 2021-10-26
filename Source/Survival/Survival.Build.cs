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
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
	}
}