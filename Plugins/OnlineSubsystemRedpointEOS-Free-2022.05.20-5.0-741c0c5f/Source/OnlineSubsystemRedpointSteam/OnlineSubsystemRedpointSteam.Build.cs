// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public class OnlineSubsystemRedpointSteam : ModuleRules
{
    public OnlineSubsystemRedpointSteam(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;

#if UE_5_0_OR_LATER
        PublicDefinitions.Add("UE_5_0_OR_LATER=1");
#endif

    }
}
