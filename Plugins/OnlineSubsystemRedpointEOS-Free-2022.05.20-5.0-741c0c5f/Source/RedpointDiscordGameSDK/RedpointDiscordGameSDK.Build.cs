// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;

public class RedpointDiscordGameSDK : ModuleRules
{
    public RedpointDiscordGameSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;
        Type = ModuleType.External;

        if (!OnlineSubsystemRedpointEOSConfig.GetBool(Target, "ENABLE_DISCORD", false))
        {
            PublicDefinitions.Add("EOS_DISCORD_ENABLED=0");
            return;
        }

        if (Target.Type == TargetType.Server)
        {
            PublicDefinitions.Add("EOS_DISCORD_ENABLED=0");
            return;
        }

        string SdkBase = LocateSdkDirectory(this, Target, ModuleDirectory);
        if (SdkBase == null)
        {
            Console.WriteLine("error: Discord support was enabled with the ONLINE_SUBSYSTEM_EOS_ENABLE_DISCORD=1 ProjectDefinition, but this machine does not have the Discord Game SDK installed. Please install it to C:\\ProgramData\\DiscordGameSDK.");
            throw new Exception("EOS Discord support is missing one or more required files");
        }

        PublicDefinitions.Add("EOS_DISCORD_ENABLED=1");

        GeneratePatchedSourceCode(SdkBase);

#if !UE_5_0_OR_LATER
        if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            PublicAdditionalLibraries.Add(Path.Combine(SdkBase, "lib", "x86", "discord_game_sdk.dll.lib"));
            RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dll", Path.Combine(SdkBase, "lib", "x86", "discord_game_sdk.dll"));
        }
        else
#endif
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(SdkBase, "lib", "x86_64", "discord_game_sdk.dll.lib"));
            RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dll", Path.Combine(SdkBase, "lib", "x86_64", "discord_game_sdk.dll"));

            try
            {
                // Copy runtime dependency so the editor will load properly.
                Directory.CreateDirectory(Path.Combine(Target.ProjectFile.Directory.FullName, "Binaries", "Win64"));
                File.Copy(
                    Path.Combine(SdkBase, "lib", "x86_64", "discord_game_sdk.dll"),
                    Path.Combine(Target.ProjectFile.Directory.FullName, "Binaries", "Win64", "discord_game_sdk.dll"),
                    true
                );
            }
            catch { }
        }

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(SdkBase),
            }
        );
    }

    private static string LocateSdkDirectory(ModuleRules Module, ReadOnlyTargetRules Target, string ModuleBase)
    {
        string[] CandidateDirectories;
        if (System.IO.Path.DirectorySeparatorChar == '\\')
        {
            CandidateDirectories = new string[]
            {
                // Where the ZIP has been extracted to "ThirdParty-DiscordGameSDK" and placed next to "RedpointDiscordGameSDK".
                Path.Combine(Path.GetFullPath(ModuleBase), "..", "ThirdParty-DiscordGameSDK"),
                // Where the ZIP has been extracted into C:\ProgramData\DiscordGameSDK\
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData), "DiscordGameSDK"),
                // Where the ZIP has been extracted into the user's downloads folder
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Downloads", "discord_game_sdk"),
                // Where the ZIP has been extracted into C:\DiscordGameSDK\
                Path.Combine(Environment.GetEnvironmentVariable("SYSTEMDRIVE"), "DiscordGameSDK"),
            };
        }
        else
        {
            CandidateDirectories = new string[]
            {
                // Where the ZIP has been extracted to "ThirdParty-DiscordGameSDK" and placed next to "RedpointDiscordGameSDK".
                Path.Combine(Path.GetFullPath(ModuleBase), "..", "ThirdParty-DiscordGameSDK"),
                // Where the SDK has been extracted into the user's downloads folder
                Path.Combine(Environment.GetEnvironmentVariable("HOME"), "Downloads", "discord_game_sdk"),
            };
        }

        foreach (var Dir in CandidateDirectories)
        {
            if (Directory.Exists(Dir))
            {
                Console.WriteLine("EOSSDK (Discord): Located Discord Game SDK at: " + Dir);
                return Dir;
            }
        }

        return null;
    }

    private void GeneratePatchedSourceCode(string SdkBase)
    {
        var generatedName = "RedpointPatched";

        Directory.CreateDirectory(Path.Combine(SdkBase, "cpp", generatedName));
        foreach (var hPath in Directory.GetFiles(Path.Combine(SdkBase, "cpp"), "*.h"))
        {
            var hFilename = Path.GetFileName(hPath);
            var originalContent = File.ReadAllText(hPath);
            var newContent = originalContent;
            if (hFilename != "event.h")
            {
                newContent = newContent.Replace("\nclass ", "\nclass REDPOINTDISCORDGAMESDKRUNTIME_API ");
            }
            var newFileName = Path.Combine(SdkBase, "cpp", generatedName, hFilename);
            if (!File.Exists(newFileName) || File.ReadAllText(newFileName) != newContent)
            {
                File.WriteAllText(newFileName, newContent);
            }
            ExternalDependencies.Add(newFileName);
        }

        foreach (var cppPath in Directory.GetFiles(Path.Combine(SdkBase, "cpp"), "*.cpp"))
        {
            var cppFilename = Path.GetFileName(cppPath);
            var originalContent = File.ReadAllText(cppPath);
            var newContent = originalContent;
            var newFileName = Path.Combine(SdkBase, "cpp", generatedName, cppFilename);
            if (!File.Exists(newFileName) || File.ReadAllText(newFileName) != newContent)
            {
                File.WriteAllText(newFileName, newContent);
            }
            ExternalDependencies.Add(newFileName);
        }
    }
}
