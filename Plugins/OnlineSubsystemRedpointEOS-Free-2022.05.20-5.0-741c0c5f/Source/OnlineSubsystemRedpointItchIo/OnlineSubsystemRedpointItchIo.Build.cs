// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public class OnlineSubsystemRedpointItchIo : ModuleRules
{
    public OnlineSubsystemRedpointItchIo(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PublicDefinitions.Add("OnlineSubsystemRedpointItchIo_CLANG_TIDY_DISPLAY_QUERY_COMMANDS=1");

    }
}
