// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;
#if UE_5_0_OR_LATER
using EpicGames.Core;
#else
using Tools.DotNETCommon;
#endif

public class RedpointEOSPlatformDefault : ModuleRules
{
    public RedpointEOSPlatformDefault(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Projects",
                "Engine",
                "OnlineSubsystem",
                "OnlineSubsystemRedpointEOS",
                "OnlineSubsystemUtils",
                "RedpointEOSSDK",
            }
        );

        if (Target.Type != TargetType.Server)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "UMG",
                }
            );
        }

    }

}
