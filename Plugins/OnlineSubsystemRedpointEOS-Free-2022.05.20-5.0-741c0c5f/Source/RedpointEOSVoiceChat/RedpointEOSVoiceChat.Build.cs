// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public class RedpointEOSVoiceChat : ModuleRules
{
    public RedpointEOSVoiceChat(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;

#if UE_5_0_OR_LATER
        PublicDefinitions.Add("UE_5_0_OR_LATER=1");
#endif
#if UE_4_27_OR_LATER
        PublicDefinitions.Add("UE_4_27_OR_LATER=1");
#endif
#if UE_4_26_OR_LATER
        PublicDefinitions.Add("UE_4_26_OR_LATER=1");
#endif
#if UE_4_25_OR_LATER
        PublicDefinitions.Add("UE_4_25_OR_LATER=1");
#endif

    }
}
