// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LevelTest : ModuleRules
{
	public LevelTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
            "NavigationSystem",
			"GameplayTasks",
			"GameplayTags"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"LevelTest",
			"LevelTest/Variant_Platforming",
			"LevelTest/Variant_Platforming/Animation",
			"LevelTest/Variant_Combat",
			"LevelTest/Variant_Combat/AI",
			"LevelTest/Variant_Combat/Animation",
			"LevelTest/Variant_Combat/Gameplay",
			"LevelTest/Variant_Combat/Interfaces",
			"LevelTest/Variant_Combat/UI",
			"LevelTest/Variant_SideScrolling",
			"LevelTest/Variant_SideScrolling/AI",
			"LevelTest/Variant_SideScrolling/Gameplay",
			"LevelTest/Variant_SideScrolling/Interfaces",
			"LevelTest/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
