// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class app_1 : ModuleRules
{
    public app_1(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
            {"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG","OnlineSubsystem","OnlineSubsystemSteam"});
    }
}