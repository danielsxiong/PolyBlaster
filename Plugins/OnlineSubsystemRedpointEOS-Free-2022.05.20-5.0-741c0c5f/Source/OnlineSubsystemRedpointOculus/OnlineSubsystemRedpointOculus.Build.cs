// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public class OnlineSubsystemRedpointOculus : ModuleRules
{
    public OnlineSubsystemRedpointOculus(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;

    }
}
