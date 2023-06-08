// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectCipher : ModuleRules
{
	public ProjectCipher(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PublicIncludePaths.AddRange(new[]
		{
			"ProjectCipher/Public/Player",
			"ProjectCipher/Public/Components",
			"ProjectCipher/Public/Environment",
			"ProjectCipher/Public/UI"
		});
	}
}