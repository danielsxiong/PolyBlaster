// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public static class OnlineSubsystemRedpointEOSConfig
{
    public static bool GetBool(ReadOnlyTargetRules Target, string Name, bool bDefaultValue)
    {
        // Prepend the ONLINE_SUBSYSTEM_EOS_ prefix.
        Name = "ONLINE_SUBSYSTEM_EOS_" + Name;

        // Try to read from the environment variables first.
        var envValue = Environment.GetEnvironmentVariable(Name);
        if (envValue != null)
        {
            if (Name != "ONLINE_SUBSYSTEM_EOS_FORCE_SDK_USAGE_FROM_PLUGIN" &&
                Name != "ONLINE_SUBSYSTEM_EOS_BUILDING_FREE_EDITION")
            {
                Console.WriteLine("WARNING: The configuration value " + Name + " is being read from an environment variable. You should remove the environment variable from your system and migrate to using 'ProjectDefinitions.Add(\"" + Name + "=1\");' in your project targets instead.");
            }

            return envValue == "true" || envValue == "1";
        }

        // Check to see if the setting is in the target's definitions.
        foreach (string definition in Target.ProjectDefinitions)
        {
            if (definition.StartsWith(Name + "="))
            {
                return definition == Name + "=1";
            }
        }

        // Otherwise fallback to default.
        return bDefaultValue;
    }

    public static string GetString(ReadOnlyTargetRules Target, string Name, string DefaultValue)
    {
        // Prepend the ONLINE_SUBSYSTEM_EOS_ prefix.
        Name = "ONLINE_SUBSYSTEM_EOS_" + Name;

        // For permitted settings, try to read from the environment variables first.
        if (Name == "ONLINE_SUBSYSTEM_EOS_FORCE_SDK_VERSION" ||
            Name.StartsWith("ONLINE_SUBSYSTEM_EOS_FORCE_SDK_VERSION_"))
        {
            var envValue = Environment.GetEnvironmentVariable(Name);
            if (!string.IsNullOrWhiteSpace(envValue))
            {
                return envValue;
            }
        }

        // Check to see if the setting is in the target's definitions.
        foreach (string definition in Target.ProjectDefinitions)
        {
            if (definition.StartsWith(Name + "="))
            {
                return definition.Split('=')[1];
            }
        }

        // Otherwise fallback to default.
        return DefaultValue;
    }
}

public class OnlineSubsystemRedpointEOS : ModuleRules
{
    public OnlineSubsystemRedpointEOS(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "OnlineSubsystemUtils",
                "Projects",
                "Json",

                // Now necessary for the EOSError.h header in Public.
                "OnlineSubsystem",

                // Now necessary as UEOSSubsystem is a UObject which depends on UUserWidget (and because it is a UObject, it can't be excluded for server-only builds).
                "UMG",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "RedpointEOSSDK",
            }
        );

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

        // Prevent implicit narrowing of types on Windows. We have to use these macros around any 
        // external headers because the engine is not compliant with these requirements, and turning 
        // them on globally causes the engine headers to fail the build.
#if UE_5_0_OR_LATER
        if (Target.Platform == UnrealTargetPlatform.Win64)
#else
        if (Target.Platform == UnrealTargetPlatform.Win32 ||
        Target.Platform == UnrealTargetPlatform.Win64)
#endif
        {
            PublicDefinitions.Add("EOS_ENABLE_STRICT_WARNINGS=__pragma(warning(push))__pragma(warning(error:4244))__pragma(warning(error:4838))");
            PublicDefinitions.Add("EOS_DISABLE_STRICT_WARNINGS=__pragma(warning(pop))");
        }
        else
        {
            PublicDefinitions.Add("EOS_ENABLE_STRICT_WARNINGS=");
            PublicDefinitions.Add("EOS_DISABLE_STRICT_WARNINGS=");
        }

    }
}

