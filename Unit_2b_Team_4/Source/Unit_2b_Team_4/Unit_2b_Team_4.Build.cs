// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unit_2b_Team_4 : ModuleRules
{
	public Unit_2b_Team_4(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Unit_2b_Team_4",
			"Unit_2b_Team_4/Variant_Horror",
			"Unit_2b_Team_4/Variant_Horror/UI",
			"Unit_2b_Team_4/Variant_Shooter",
			"Unit_2b_Team_4/Variant_Shooter/AI",
			"Unit_2b_Team_4/Variant_Shooter/UI",
			"Unit_2b_Team_4/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
