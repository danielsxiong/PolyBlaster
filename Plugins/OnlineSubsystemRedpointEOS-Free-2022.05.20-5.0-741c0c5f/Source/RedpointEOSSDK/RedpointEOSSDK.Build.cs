// Copyright June Rhodes. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;

public struct RedpointEOSSDKVersionConstraints
{
    /**
     * SDK versions will not be allowed until this SDK version is hit in
     * the SDK version preference list.
     */
    public string MaximumTolerableSDKVersion;

    /**
     * These SDK versions will never be used. This list is used to exclude
     * SDK versions that are known to be broken on a given platform.
     */
    public string[] SDKVersionDenyList;
}

public interface IRedpointEOSPlatform
{
    bool IsActive(ReadOnlyTargetRules Target);

    string GetPlatformSuffix();

    void ConfigureModule(string SdkBase, string ModuleBase, ModuleRules Module, ReadOnlyTargetRules Target);

    RedpointEOSSDKVersionConstraints GetSDKVersionConstraints();
}

public static class RedpointEOSCommonConstraints
{
    public static RedpointEOSSDKVersionConstraints GetDesktopSDKVersionConstraints()
    {
        // Awful hack to get around 1.14.1 having different revision numbers for different platforms. This prevents
        // desktop builds from using the older revision (18059966-v1.14.1) in Free Edition builds while still allowing
        // mobile builds to use the only (older) revision they have available.

            var Constraints = new RedpointEOSSDKVersionConstraints();
            Constraints.SDKVersionDenyList = new string[]
            {
                "18059966-v1.14.1"
            };
            return Constraints;

    }
}

#if !UE_5_0_OR_LATER
/// <summary>
/// Win32 platform support for EOS.
/// </summary>
public class RedpointEOSPlatform_Win32 : IRedpointEOSPlatform
{
    public bool IsActive(ReadOnlyTargetRules Target)
    {
        return Target.Platform == UnrealTargetPlatform.Win32;
    }

    public string GetPlatformSuffix()
    {
        return string.Empty;
    }

    public void ConfigureModule(string SdkBase, string ModuleBase, ModuleRules Module, ReadOnlyTargetRules Target)
    {
        Module.PublicIncludePaths.Add(Path.Combine(SdkBase, "Include"));
        Module.PublicAdditionalLibraries.Add(Path.Combine(SdkBase, "Lib", "EOSSDK-Win32-Shipping.lib"));
        Module.RuntimeDependencies.Add("$(TargetOutputDir)/RedpointEOS/EOSSDK-Win32-Shipping.dll", Path.Combine(SdkBase, "Bin", "EOSSDK-Win32-Shipping.dll"));
        if (File.Exists(Path.Combine(SdkBase, "Bin", "x86", "xaudio2_9redist.dll")))
        {
            Module.RuntimeDependencies.Add("$(TargetOutputDir)/RedpointEOS/x86/xaudio2_9redist.dll", Path.Combine(SdkBase, "Bin", "x86", "xaudio2_9redist.dll"));
        }
        Module.PublicDelayLoadDLLs.Add("EOSSDK-Win32-Shipping.dll");
        Module.ExternalDependencies.Add(Path.Combine(SdkBase, "Include", "eos_version.h"));

        RedpointEOSSDK.EnsureDirectoryExists(new[] {
            Path.Combine(SdkBase, "Include"),
        });
        RedpointEOSSDK.EnsureFilesExist(new[] {
            Path.Combine(SdkBase, "Include", "eos_version.h"),
            Path.Combine(SdkBase, "Lib", "EOSSDK-Win32-Shipping.lib"),
            Path.Combine(SdkBase, "Bin", "EOSSDK-Win32-Shipping.dll")
        });
    }

    public RedpointEOSSDKVersionConstraints GetSDKVersionConstraints()
    {
        return RedpointEOSCommonConstraints.GetDesktopSDKVersionConstraints();
    }
}
#endif

/// <summary>
/// Win64 platform support for EOS.
/// </summary>
public class RedpointEOSPlatform_Win64 : IRedpointEOSPlatform
{
    public bool IsActive(ReadOnlyTargetRules Target)
    {
        return Target.Platform == UnrealTargetPlatform.Win64;
    }

    public string GetPlatformSuffix()
    {
        return string.Empty;
    }

    public void ConfigureModule(string SdkBase, string ModuleBase, ModuleRules Module, ReadOnlyTargetRules Target)
    {
        Module.PublicIncludePaths.Add(Path.Combine(SdkBase, "Include"));
        Module.PublicAdditionalLibraries.Add(Path.Combine(SdkBase, "Lib", "EOSSDK-Win64-Shipping.lib"));
        Module.RuntimeDependencies.Add("$(TargetOutputDir)/RedpointEOS/EOSSDK-Win64-Shipping.dll", Path.Combine(SdkBase, "Bin", "EOSSDK-Win64-Shipping.dll"));
        if (File.Exists(Path.Combine(SdkBase, "Bin", "x86", "xaudio2_9redist.dll")))
        {
            Module.RuntimeDependencies.Add("$(TargetOutputDir)/RedpointEOS/x64/xaudio2_9redist.dll", Path.Combine(SdkBase, "Bin", "x64", "xaudio2_9redist.dll"));
        }
        Module.PublicDelayLoadDLLs.Add("EOSSDK-Win64-Shipping.dll");
        Module.ExternalDependencies.Add(Path.Combine(SdkBase, "Include", "eos_version.h"));

        RedpointEOSSDK.EnsureDirectoryExists(new[] {
            Path.Combine(SdkBase, "Include"),
        });
        RedpointEOSSDK.EnsureFilesExist(new[] {
            Path.Combine(SdkBase, "Include", "eos_version.h"),
            Path.Combine(SdkBase, "Lib", "EOSSDK-Win64-Shipping.lib"),
            Path.Combine(SdkBase, "Bin", "EOSSDK-Win64-Shipping.dll")
        });
    }

    public RedpointEOSSDKVersionConstraints GetSDKVersionConstraints()
    {
        return RedpointEOSCommonConstraints.GetDesktopSDKVersionConstraints();
    }
}

/// <summary>
/// macOS platform support for EOS.
/// </summary>
public class RedpointEOSPlatform_Mac : IRedpointEOSPlatform
{
    public bool IsActive(ReadOnlyTargetRules Target)
    {
        return Target.Platform == UnrealTargetPlatform.Mac;
    }

    public string GetPlatformSuffix()
    {
        return string.Empty;
    }

    public void ConfigureModule(string SdkBase, string ModuleBase, ModuleRules Module, ReadOnlyTargetRules Target)
    {
        Module.PublicIncludePaths.Add(Path.Combine(SdkBase, "Include"));
        // UBT adds the source path of the runtime dependency to the RPATH, not the destination path where the 
        // file will be located. When we use $(TargetOutputDir) on macOS, packaged games will crash because 
        // the /Contents/UE4/<project>/Binaries/Mac/ path doesn't get added as an RPATH.
        //
        // So instead, we have to put the library in a location that will already be on the RPATH. 
        // $(BinaryOutputDir) resolves to the /Contents/MacOS/ directory, where the main executable file is, 
        // and this is also on the RPATH.
        //
        // Note that this change also impacts EOSDynamicLoaderDefault. Refer to the comment on line 78 of
        // EOSDynamicLoaderDefault.cpp to see how the loader accesses this alternate path.
        if (Environment.GetEnvironmentVariable("BUILDING_FOR_REDISTRIBUTION") != "true")
        {
            Module.RuntimeDependencies.Add("$(BinaryOutputDir)/libEOSSDK-Mac-Shipping.dylib", Path.Combine(SdkBase, "Bin", "libEOSSDK-Mac-Shipping.dylib"));
        }
        else
        {
            // If the environment variable BUILDING_FOR_REDISTRIBUTION is set to true, then we are building the plugin for
            // redistribution (Free Edition). When building the plugin, $(BinaryOutputDir) maps to a folder within the
            // plugin's folder. However, building the plugin for redistribution doesn't cause the EOS SDK to be copied here.
            //
            // In the past, we used BuildPlugin, which didn't care if the output artifacts of the build didn't exist. We now
            // use BuildGraph however, and it *does* check to make sure all the output artifacts exist. This causes the build to
            // fail if we're using $(BinaryOutputDir).
            //
            // However, in these cases we know that we're building the Free Edition and that the developer will need to provide
            // their own copy of the EOS SDK (which will cause the above branch to run and have the EOS SDK copied out to
            // BinaryOutputDir correctly). So use this workaround so that the build will pass under BuildGraph.
            Module.RuntimeDependencies.Add("$(TargetOutputDir)/libEOSSDK-Mac-Shipping.dylib", Path.Combine(SdkBase, "Bin", "libEOSSDK-Mac-Shipping.dylib"));
        }
        Module.PublicDelayLoadDLLs.Add(Path.Combine(SdkBase, "Bin", "libEOSSDK-Mac-Shipping.dylib"));
        Module.ExternalDependencies.Add(Path.Combine(SdkBase, "Include", "eos_version.h"));

        // If the user has EAS credentials installed for unit tests, copy across the JSON file so that the test can
        // execute on device.
        var easCredentialsPath = RedpointEOSSDK.LocateEASAutomatedTestingCredentialsPath(Target);
        if (easCredentialsPath != null)
        {
            Module.RuntimeDependencies.Add("$(TargetOutputDir)/Credentials.json", easCredentialsPath);
        }

        RedpointEOSSDK.EnsureDirectoryExists(new[] {
            Path.Combine(SdkBase, "Include"),
        });
        RedpointEOSSDK.EnsureFilesExist(new[] {
            Path.Combine(SdkBase, "Include", "eos_version.h"),
            Path.Combine(SdkBase, "Bin", "libEOSSDK-Mac-Shipping.dylib")
        });
    }

    public RedpointEOSSDKVersionConstraints GetSDKVersionConstraints()
    {
        return RedpointEOSCommonConstraints.GetDesktopSDKVersionConstraints();
    }
}

/// <summary>
/// Linux platform support for EOS.
/// </summary>
public class RedpointEOSPlatform_Linux : IRedpointEOSPlatform
{
    public bool IsActive(ReadOnlyTargetRules Target)
    {
        return Target.Platform == UnrealTargetPlatform.Linux;
    }

    public string GetPlatformSuffix()
    {
        return string.Empty;
    }

    public void ConfigureModule(string SdkBase, string ModuleBase, ModuleRules Module, ReadOnlyTargetRules Target)
    {
        Module.PublicIncludePaths.Add(Path.Combine(SdkBase, "Include"));
        Module.PublicAdditionalLibraries.Add(Path.Combine(SdkBase, "Bin", "libEOSSDK-Linux-Shipping.so"));
        Module.RuntimeDependencies.Add("$(TargetOutputDir)/libEOSSDK-Linux-Shipping.so", Path.Combine(SdkBase, "Bin", "libEOSSDK-Linux-Shipping.so"));
        Module.ExternalDependencies.Add(Path.Combine(SdkBase, "Include", "eos_version.h"));

        RedpointEOSSDK.EnsureDirectoryExists(new[] {
            Path.Combine(SdkBase, "Include"),
        });
        RedpointEOSSDK.EnsureFilesExist(new[] {
            Path.Combine(SdkBase, "Include", "eos_version.h"),
            Path.Combine(SdkBase, "Bin", "libEOSSDK-Linux-Shipping.so")
        });
    }

    public RedpointEOSSDKVersionConstraints GetSDKVersionConstraints()
    {
        return RedpointEOSCommonConstraints.GetDesktopSDKVersionConstraints();
    }
}

/// <summary>
/// iOS platform support for EOS.
/// </summary>
public class RedpointEOSPlatform_IOS : IRedpointEOSPlatform
{
    public bool IsActive(ReadOnlyTargetRules Target)
    {
        return Target.Platform == UnrealTargetPlatform.IOS;
    }

    public string GetPlatformSuffix()
    {
        return "-IOS";
    }

    public void ConfigureModule(string SdkBase, string ModuleBase, ModuleRules Module, ReadOnlyTargetRules Target)
    {
        Module.PublicIncludePaths.Add(Path.Combine(SdkBase, "Bin", "IOS", "EOSSDK.framework", "Headers"));
        Module.ExternalDependencies.Add(Path.Combine(SdkBase, "Bin", "IOS", "EOSSDK.framework", "Headers", "eos_version.h"));
        Module.AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(ModuleBase, "RedpointEOSSDK_IOS_UPL.xml"));

        // If the user has EAS credentials installed for unit tests, copy across the JSON file so that the test can
        // execute on device.
        var easCredentialsPath = RedpointEOSSDK.LocateEASAutomatedTestingCredentialsPath(Target);
        if (easCredentialsPath != null)
        {
            Module.RuntimeDependencies.Add("$(TargetOutputDir)/Credentials.json", easCredentialsPath);
        }

        // For iOS 11, use SafariServices. For iOS 12 and greater, use AuthenticationServices.
        if (Target.IOSPlatform.RuntimeVersion < 12.0f)
        {
            Console.WriteLine("EOSSDK (IOS): Using SafariServices framework because this project is targeting iOS " + Target.IOSPlatform.RuntimeVersion);
            Module.PublicFrameworks.Add("SafariServices");
        }
        else
        {
            Console.WriteLine("EOSSDK (IOS): Using AuthenticationServices framework because this project is targeting iOS " + Target.IOSPlatform.RuntimeVersion);
            Module.PublicFrameworks.Add("AuthenticationServices");
        }

        // For iOS 13, we must pass PresentationContextProviding for authentication.
        if (Target.IOSPlatform.RuntimeVersion >= 13.0f)
        {
            Console.WriteLine("EOSSDK (IOS): Enabling PresentationContext code as this project is targeting iOS " + Target.IOSPlatform.RuntimeVersion);
            Module.PublicDefinitions.Add("EOS_IOS_REQUIRES_PRESENTATIONCONTEXT=1");
        }
        else
        {
            Console.WriteLine("EOSSDK (IOS): Not enabling PresentationContext code as this project is targeting iOS " + Target.IOSPlatform.RuntimeVersion);
            Module.PublicDefinitions.Add("EOS_IOS_REQUIRES_PRESENTATIONCONTEXT=0");
        }

        // We have to generate a ZIP file, because that is the only way Unreal Engine supports adding
        // external frameworks on iOS.
        string FrameworkDirectory = Path.Combine(SdkBase, "Bin", "IOS", "EOSSDK.framework");
        string FrameworkPath = Path.Combine(SdkBase, "Bin", "IOS", "EOSSDK.embeddedframework.zip");
        if (File.Exists(FrameworkPath))
        {
            if (Environment.GetEnvironmentVariable("GITLAB_CI") == "true" &&
                Environment.GetEnvironmentVariable("CI_PROJECT_NAMESPACE") == "redpointgames")
            {
                // Ensure we always attempt to run the zip command below when building on GitLab CI/CD, to ensure that the command
                // continues to work with newer version of macOS and Xcode, and isn't reliant on a cached version of the file.
                Console.WriteLine("EOSSDK (IOS): Deleting cached EOSSDK.embeddedframework.zip to ensure correctness because this build is running on GitLab CI/CD.");
                File.Delete(FrameworkPath);
            }
        }
        if (!File.Exists(FrameworkPath) && Directory.Exists(FrameworkDirectory))
        {
            var target = Path.Combine(Path.GetTempPath(), "EOSSDK.embeddedframework");
            Console.WriteLine("EOSSDK (IOS): Generating EOSSDK.embeddedframework.zip for Unreal Engine on iOS...");
            if (Directory.Exists(target))
            {
                Directory.Delete(target, true);
            }
            Directory.CreateDirectory(target);
            Directory.CreateDirectory(Path.Combine(target, "EOSSDK.embeddedframework"));
            DirectoryCopy(
                FrameworkDirectory,
                Path.Combine(target, "EOSSDK.embeddedframework", "EOSSDK.framework"),
                true);
#if UE_5_0_OR_LATER
            Console.WriteLine("EOSSDK (IOS): Using ZipFile.CreateFromDirectory to generate ZIP...");
            var assembly = Assembly.Load("System.IO.Compression.ZipFile");
            var type = assembly.GetType("System.IO.Compression.ZipFile");
            var method = type.GetMethods(BindingFlags.Public | BindingFlags.Static).FirstOrDefault(x => x.Name == "CreateFromDirectory" && x.GetParameters().Length == 4);
            var compressionAssembly = Assembly.Load("System.IO.Compression");
            var fastestValue = Enum.GetValues(compressionAssembly.GetType("System.IO.Compression.CompressionLevel")).GetValue(1);
            method.Invoke(null, new object[] {
                target,
                FrameworkPath,
                fastestValue,
                false
            });
#else
            Console.WriteLine("EOSSDK (IOS): Executing /usr/bin/zip -r '" + FrameworkPath + "' . (in " + target + ")");
            var zipStart = new ProcessStartInfo
            {
                FileName = "/usr/bin/zip",
                Arguments = "-r '" + FrameworkPath + "' .",
                WorkingDirectory = target,
            };
            var zipProc = Process.Start(zipStart);
            zipProc.WaitForExit();
            if (zipProc.ExitCode != 0)
            {
                throw new Exception("Unable to generate EOSSDK.embeddedframework.zip for iOS build!");
            }
#endif
            Console.WriteLine("EOSSDK (IOS): Generated EOSSDK.embeddedframework.zip for iOS to: " + FrameworkPath);
        }
        else if (File.Exists(FrameworkPath))
        {
            Console.WriteLine("EOSSDK (IOS): Using cached EOSSDK.embeddedframework.zip for Unreal Engine on iOS.");
        }

        // Add the EOS SDK as an embedded framework.
        Module.PublicAdditionalFrameworks.Add(new ModuleRules.Framework(
            "EOSSDK",
            FrameworkPath,
            ""
        ));

        // Generate a Frameworks folder and tell the build to copy it into the
        // app bundle with AdditionalBundleResources. UE4's build process does not
        // currently support embedding dynamic frameworks, so we have to do it
        // manually.
        var frameworksDir = Path.Combine(Path.GetTempPath(), "EOSSDK-Frameworks", "Frameworks");
        Directory.CreateDirectory(Path.Combine(frameworksDir, "EOSSDK.framework"));
        if (!File.Exists(Path.Combine(frameworksDir, "EOSSDK.framework", "EOSSDK")))
        {
            File.Copy(
                Path.Combine(FrameworkDirectory, "EOSSDK"),
                Path.Combine(frameworksDir, "EOSSDK.framework", "EOSSDK")
            );
        }
        if (!File.Exists(Path.Combine(frameworksDir, "EOSSDK.framework", "Info.plist")))
        {
            File.Copy(
                Path.Combine(FrameworkDirectory, "Info.plist"),
                Path.Combine(frameworksDir, "EOSSDK.framework", "Info.plist")
            );
        }
        Module.AdditionalBundleResources.Add(new ModuleRules.BundleResource(frameworksDir));

        RedpointEOSSDK.EnsureDirectoryExists(new[] {
            Path.Combine(FrameworkDirectory, "Headers"),
            frameworksDir,
        });
        RedpointEOSSDK.EnsureFilesExist(new[] {
            Path.Combine(FrameworkDirectory, "Headers", "eos_version.h"),
            FrameworkPath,
        });
    }

    private static void DirectoryCopy(string sourceDirName, string destDirName,
                                      bool copySubDirs)
    {
        DirectoryInfo dir = new DirectoryInfo(sourceDirName);
        if (!dir.Exists)
        {
            throw new DirectoryNotFoundException(
                "Source directory does not exist or could not be found: "
                + sourceDirName);
        }
        DirectoryInfo[] dirs = dir.GetDirectories();
        if (!Directory.Exists(destDirName))
        {
            Directory.CreateDirectory(destDirName);
        }
        FileInfo[] files = dir.GetFiles();
        foreach (FileInfo file in files)
        {
            string temppath = Path.Combine(destDirName, file.Name);
            file.CopyTo(temppath, false);
        }
        if (copySubDirs)
        {
            foreach (DirectoryInfo subdir in dirs)
            {
                string temppath = Path.Combine(destDirName, subdir.Name);
                DirectoryCopy(subdir.FullName, temppath, copySubDirs);
            }
        }
    }

    public RedpointEOSSDKVersionConstraints GetSDKVersionConstraints()
    {
        return default(RedpointEOSSDKVersionConstraints);
    }
}

/// <summary>
/// Android platform support for EOS.
/// </summary>
public class RedpointEOSPlatform_Android : IRedpointEOSPlatform
{
    public bool IsActive(ReadOnlyTargetRules Target)
    {
        return Target.Platform == UnrealTargetPlatform.Android;
    }

    public string GetPlatformSuffix()
    {
        return "-Android";
    }

    public void ConfigureModule(string SdkBase, string ModuleBase, ModuleRules Module, ReadOnlyTargetRules Target)
    {
        Module.PublicIncludePaths.Add(Path.Combine(SdkBase, "Bin", "Android", "include"));
        Module.PublicAdditionalLibraries.Add(Path.Combine(SdkBase, "Bin", "Android", "libs", "armeabi-v7a", "libEOSSDK.so"));
        Module.PublicAdditionalLibraries.Add(Path.Combine(SdkBase, "Bin", "Android", "libs", "arm64-v8a", "libEOSSDK.so"));
        Module.ExternalDependencies.Add(Path.Combine(SdkBase, "Bin", "Android", "include", "eos_version.h"));

        // If the user has EAS credentials installed for unit tests, copy across the JSON file so that the test can
        // execute on device.
        var easCredentialsPath = RedpointEOSSDK.LocateEASAutomatedTestingCredentialsPath(Target);
        if (easCredentialsPath != null)
        {
            Module.RuntimeDependencies.Add("$(TargetOutputDir)/Credentials.json", easCredentialsPath);
        }

        // We have to generate our _UPL.xml file, because we have to add the EOS SDK path to it. There is not really a way
        // to dynamically pass variables from here into a UPL, other than generating the UPL file.
#if UE_5_0_OR_LATER
        var BaseTheme = "UnrealBaseTheme";
#else
        var BaseTheme = "UE4BaseTheme";
#endif
        var UPLTemplate = @"
<?xml version=""1.0"" encoding=""utf-8""?>
<root xmlns:android=""http://schemas.android.com/apk/res/android"">
    <init>
        <log text=""EOS SDK added, using SDK path: __SDK_PATH__""/>
        <setStringFromProperty result=""ClientId"" ini=""Engine"" section=""EpicOnlineServices"" property=""ClientId"" default=""THIS_APP_DOES_NOT_SUPPORT_EAS"" />

        <!-- The only way to lowercase this string... -->
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""A"" with=""a""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""B"" with=""b""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""C"" with=""c""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""D"" with=""d""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""E"" with=""e""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""F"" with=""f""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""G"" with=""g""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""H"" with=""h""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""I"" with=""i""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""J"" with=""j""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""K"" with=""k""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""L"" with=""l""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""M"" with=""m""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""N"" with=""n""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""O"" with=""o""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""P"" with=""p""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""Q"" with=""q""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""R"" with=""r""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""S"" with=""s""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""T"" with=""t""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""U"" with=""u""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""V"" with=""v""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""W"" with=""w""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""X"" with=""x""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""Y"" with=""y""/>
        <setStringReplace result=""ClientId"" source=""$S(ClientId)"" find=""Z"" with=""z""/>
    </init>

    <baseBuildGradleAdditions>
        <insert>
            allprojects {
                repositories {
                    repositories {
                        flatDir {
        </insert>
        <insertValue value=""dirs '__SDK_PATH__/Bin/Android/aar'""/>
        <insertNewline/>
        <insert>
                        }
                    }
                }
            }

            allprojects {
              def mappings = [
                'android.support.annotation': 'androidx.annotation',
                'android.arch.lifecycle': 'androidx.lifecycle',
                'android.support.v4.app.NotificationCompat': 'androidx.core.app.NotificationCompat',
                'android.support.v4.app.NotificationManagerCompat': 'androidx.core.app.NotificationManagerCompat',
                'android.support.v4.app.ActivityCompat': 'androidx.core.app.ActivityCompat',
                'android.support.v4.content.ContextCompat': 'androidx.core.content.ContextCompat',
                'android.support.v13.app.FragmentCompat': 'androidx.legacy.app.FragmentCompat',
                'android.support.v4.content.FileProvider': 'androidx.core.content.FileProvider',
                'android.arch.lifecycle.Lifecycle': 'androidx.lifecycle.Lifecycle',
                'android.arch.lifecycle.LifecycleObserver': 'androidx.lifecycle.LifecycleObserver',
                'android.arch.lifecycle.OnLifecycleEvent': 'androidx.lifecycle.OnLifecycleEvent',
                'android.arch.lifecycle.ProcessLifecycleOwner': 'androidx.lifecycle.ProcessLifecycleOwner',
              ]

              beforeEvaluate { project ->
                project.rootProject.projectDir.traverse(type: groovy.io.FileType.FILES, nameFilter: ~/.*\.java$/) { f ->
                  mappings.each { entry ->
                    if (f.getText('UTF-8').contains(entry.key)) {
                      println ""Updating ${entry.key} to ${entry.value} in file ${f}""
                      ant.replace(file: f, token: entry.key, value: entry.value)
                    }
                  }
                }
              }
            }
        </insert>
    </baseBuildGradleAdditions>

    <gradleProperties>
        <insert>
            android.useAndroidX=true
            android.enableJetifier=true
        </insert>
    </gradleProperties>

    <androidManifestUpdates>
        <addAttribute tag=""application"" name=""android:theme"" value=""@style/" + BaseTheme + @""" />
        <!-- Required to access OBB files when targeting minimum SDK 23, which we will be. -->
        <addPermission android:name=""android.permission.READ_EXTERNAL_STORAGE""/>
    </androidManifestUpdates>

    <buildGradleAdditions>
        <insert>
            android {
                preBuild {
                    doFirst {
        </insert>
        <insertValue value=""def stringDefine = &quot;&lt;string name=\&quot;eos_login_protocol_scheme\&quot;&gt;eos.$S(ClientId)&lt;/string&gt;&quot;""/>
        <insertNewline />
        <insert>

                        def stringsXml = new File(""${project.projectDir}/src/main/res/values/strings.xml"")
                        if (stringsXml.exists() &amp;&amp; !stringsXml.text.contains(stringDefine)) {
                            println ""Adding eos_login_protocol_scheme string to strings.xml""
                            stringsXml.text = stringsXml.text.replaceAll(
                                ""&lt;/resources&gt;"",
                                stringDefine + ""&lt;/resources&gt;""
                            )
                        }

                        def stylesXml = new File(""${project.projectDir}/src/main/res/values/styles.xml"")
                        if (stylesXml.exists() &amp;&amp; !stylesXml.text.contains(""@style/Theme.AppCompat.NoActionBar"")) {
                            println ""Fixing up styles in values/styles.xml""
                            stylesXml.text = stylesXml.text.replaceAll(
                                ""@android:style/Theme.Black.NoTitleBar.Fullscreen\&quot; /&gt;"",
                                ""Theme.AppCompat.NoActionBar\&quot;&gt;&lt;item name=\&quot;android:windowNoTitle\&quot;&gt;true&lt;/item&gt;&lt;item name=\&quot;android:windowActionBar\&quot;&gt;false&lt;/item&gt;&lt;item name=\&quot;android:windowFullscreen\&quot;&gt;true&lt;/item&gt;&lt;item name=\&quot;android:windowContentOverlay\&quot;&gt;@null&lt;/item&gt;&lt;/style&gt;""
                            )
                        }

                        def stylesLandXml = new File(""${project.projectDir}/src/main/res/values-land/styles.xml"")
                        if (stylesLandXml.exists() &amp;&amp; !stylesLandXml.text.contains(""@style/Theme.AppCompat.NoActionBar"")) {
                            println ""Fixing up styles in values-land/styles.xml""
                            stylesLandXml.text = stylesLandXml.text.replaceAll(
                                ""@android:style/Theme.Black.NoTitleBar.Fullscreen\&quot; /&gt;"",
                                ""Theme.AppCompat.NoActionBar\&quot;&gt;&lt;item name=\&quot;android:windowNoTitle\&quot;&gt;true&lt;/item&gt;&lt;item name=\&quot;android:windowActionBar\&quot;&gt;false&lt;/item&gt;&lt;item name=\&quot;android:windowFullscreen\&quot;&gt;true&lt;/item&gt;&lt;item name=\&quot;android:windowContentOverlay\&quot;&gt;@null&lt;/item&gt;&lt;/style&gt;""
                            )
                        }
                    }
                }
            }

            android {
                packagingOptions {
                    exclude 'build-data.properties'
                }
            }

            dependencies {
                implementation 'androidx.appcompat:appcompat:1.1.0'
                implementation 'androidx.constraintlayout:constraintlayout:1.1.3'
                implementation 'androidx.security:security-crypto:1.0.0-rc03'
            }

__DEPS_LIST__
        </insert>
    </buildGradleAdditions>

    <gameActivityImportAdditions>
        <insert>
            import com.epicgames.mobile.eossdk.EOSSDK;
        </insert>
    </gameActivityImportAdditions>

    <gameActivityOnCreateAdditions>
        <insert>
			Log.debug(""Setting EOS internal directory to: "" + InternalFilesDir);
            Log.debug(""Setting EOS external directory to: "" + ExternalFilesDir);
            this.nativeSetEOSCacheDirectories(InternalFilesDir, ExternalFilesDir);
            Log.debug(""Initializing the EOS SDK on Android..."");
            EOSSDK.init(getApplicationContext());
        </insert>
    </gameActivityOnCreateAdditions>

	<soLoadLibrary>
		<loadLibrary name=""EOSSDK"" failmsg=""The EOS SDK could not be loaded, and is required to run the application."" />
	</soLoadLibrary>

    <gameActivityClassAdditions>
        <insert>
            public native void nativeSetEOSCacheDirectories(String InternalPath, String ExternalPath);
        </insert>
    </gameActivityClassAdditions>

</root>
";

        var DepsEntries = new List<string>();
        foreach (var file in Directory.GetFiles(Path.Combine(SdkBase, "Bin", "Android", "aar"), "*.aar"))
        {
            DepsEntries.Add("            dependencies.implementation(name: '" + Path.GetFileNameWithoutExtension(file) + "', ext: 'aar')");
        }

        var UPLContent = UPLTemplate.Replace("__SDK_PATH__", SdkBase.Replace('\\', '/')).Replace("__DEPS_LIST__", string.Join("\n", DepsEntries));

        // Write out the new UPL file (but don't touch it if it already matches to prevent
        // unnecessary rebuilding).
        var UPLPath = Path.Combine(ModuleBase, "RedpointEOSSDK_Android_UPL.xml");
        var ExistingUPLContent = string.Empty;
        if (File.Exists(UPLPath))
        {
            ExistingUPLContent = File.ReadAllText(UPLPath);
        }
        if (UPLContent.Trim() != ExistingUPLContent.Trim())
        {
            File.WriteAllText(UPLPath, UPLContent.Trim());
        }

        Module.AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleBase, "RedpointEOSSDK_Android_UPL.xml"));

        RedpointEOSSDK.EnsureDirectoryExists(new[] {
            Path.Combine(SdkBase, "Bin", "Android", "include"),
            Path.Combine(SdkBase, "Bin", "Android", "aar"),
        });
        RedpointEOSSDK.EnsureFilesExist(new[] {
            Path.Combine(SdkBase, "Bin", "Android", "include", "eos_version.h"),
            Path.Combine(SdkBase, "Bin", "Android", "libs", "armeabi-v7a", "libEOSSDK.so"),
            Path.Combine(SdkBase, "Bin", "Android", "libs", "arm64-v8a", "libEOSSDK.so"),
            Path.Combine(ModuleBase, "RedpointEOSSDK_Android_UPL.xml"),
        });
    }

    public RedpointEOSSDKVersionConstraints GetSDKVersionConstraints()
    {
        return default(RedpointEOSSDKVersionConstraints);
    }
}

public class RedpointEOSSDK : ModuleRules
{
    // The precompiled remove settings must exclude all versions
    // except the one set by ONLINE_SUBSYSTEM_EOS_FORCE_SDK_VERSION during
    // the Free Edition builds.
    //
    // NOTE: You must also update SignProjectForAntiCheat.ps1 when adding
    // a new version here!
    static readonly string[] EOSSDKSupportedVersions = new string[]
    {
        "18950192-v1.14.2-hf-1",

    };

    public RedpointEOSSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bUsePrecompiled = true;
        Type = ModuleType.External;

        string EOSSDKFullVersion;
        RedpointEOSSDK.AddToModule(this, Target, out EOSSDKFullVersion);

        PublicDefinitions.Add("EOS_SDK_LINK_VERSION=\"" + EOSSDKFullVersion + "\"");

        // Only 1.10 and above use the new platform-specific build infrastructure.
        if (EOSSDKFullVersion != "14547226-1.9" &&
            EOSSDKFullVersion != "14316386-1.8" &&
            EOSSDKFullVersion != "14092722-1.7.1" &&
            EOSSDKFullVersion != "13992660-1.7.1" &&
            EOSSDKFullVersion != "13812567-1.7" &&
            !Target.IsInPlatformGroup(UnrealPlatformGroup.Windows) &&
            !Target.IsInPlatformGroup(UnrealPlatformGroup.Unix) &&
            !Target.IsInPlatformGroup(UnrealPlatformGroup.Apple) &&
            !Target.IsInPlatformGroup(UnrealPlatformGroup.Android))
        {
            bool bHasEOSBuildPlatformNameOverride = false;
            foreach (string Definition in PublicDefinitions)
            {
                if (Definition.StartsWith("EOS_BUILD_PLATFORM_NAME="))
                {
                    bHasEOSBuildPlatformNameOverride = true;
                    break;
                }
            }
            if (!bHasEOSBuildPlatformNameOverride)
            {
                PublicDefinitions.Add("EOS_BUILD_PLATFORM_NAME=" + Target.Platform.ToString() + "");
            }
        }

#if UE_4_27_OR_LATER && !UE_5_0_OR_LATER
        if (Target.bBuildAllModules)
        {
            // We are building the plugin for Marketplace distribution. In this case, our
            // RuntimeDependencies declaration will conflict with the broken EOSSDK module
            // that Epic ships in 4.27 and prevent us from building, even though the broken
            // EOSSDK module won't be used by developers at runtime.
            //
            // Since RuntimeDependencies doesn't have any effect on the built plugin layout
            // (it only applies when building games), we just remove all of our RuntimeDependencies
            // to avoid any potential conflicts.
            //
            // Of course, RuntimeDependencies isn't just a list - it's a wrapper class that
            // only has Add and hides the list internally. So we have to clear things out
            // using reflection.... :(
            RuntimeDependencies.GetType().GetField("Inner", BindingFlags.NonPublic | BindingFlags.Instance).SetValue(RuntimeDependencies, new List<RuntimeDependency>());
        }
#endif
    }

    public static void EnsureDirectoryExists(string[] Paths)
    {
        foreach (var RelPath in Paths)
        {
            var FullPath = Path.GetFullPath(RelPath);
            if (string.IsNullOrWhiteSpace(FullPath))
            {
                Console.WriteLine("ERROR: Unable to locate a directory that was expected to exist in the EOS SDK. Download and re-extract the SDK to ensure that it has all the required directories. The file that was missing was: " + RelPath);
                throw new Exception("EOS SDK is missing one or more required files");
            }
            if (!Directory.Exists(FullPath))
            {
                Console.WriteLine("ERROR: Unable to locate a directory that was expected to exist in the EOS SDK. Download and re-extract the SDK to ensure that it has all the required directories. The file that was missing was: " + FullPath);
                throw new Exception("EOS SDK is missing one or more required files");
            }
        }
    }

    public static void EnsureFilesExist(string[] Paths)
    {
        foreach (var RelPath in Paths)
        {
            var FullPath = Path.GetFullPath(RelPath);
            if (string.IsNullOrWhiteSpace(FullPath))
            {
                Console.WriteLine("ERROR: Unable to locate a file that was expected to exist in the EOS SDK. Download and re-extract the SDK to ensure that it has all the required files. The file that was missing was: " + RelPath);
                throw new Exception("EOS SDK is missing one or more required files");
            }
            if (!File.Exists(FullPath))
            {
                Console.WriteLine("ERROR: Unable to locate a file that was expected to exist in the EOS SDK. Download and re-extract the SDK to ensure that it has all the required files. The file that was missing was: " + FullPath);
                throw new Exception("EOS SDK is missing one or more required files");
            }
        }
    }

    /// <summary>
    /// When we want to run unit tests on device, they won't be able to authenticate with EAS unless we copy across the credentials from the current machine onto the device we are building for. This function is used by devices to find the file to copy.
    /// 
    /// EAS credentials are never available in shipping builds.
    /// </summary>
    /// <returns></returns>
    public static string LocateEASAutomatedTestingCredentialsPath(ReadOnlyTargetRules Target)
    {
        if (Target.Configuration == UnrealTargetConfiguration.Shipping)
        {
            return null;
        }

        var searchablePaths = new List<string>();
        if (Environment.GetEnvironmentVariable("EAS_AUTOMATED_TESTING_CREDENTIAL_PATH") != null)
        {
            searchablePaths.Add(Environment.GetEnvironmentVariable("EAS_AUTOMATED_TESTING_CREDENTIAL_PATH"));
        }
        searchablePaths.Add(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Projects", "eas-automated-testing-credentials", "Credentials.json"));
        foreach (var path in searchablePaths)
        {
            if (File.Exists(path))
            {
                Console.WriteLine("EOSSDK (Unit Tests): Located automated testing credentials at path: " + path + ". They will be packaged with the game.");
                return path;
            }
        }
        return null;
    }

    private static void AddToModule(ModuleRules Module, ReadOnlyTargetRules Target, out string EOSSDKFullVersion)
    {
        // Locate the platform implementation.
        IRedpointEOSPlatform SelectedPlatform = null;
        foreach (var PlatformImplementationType in AppDomain.CurrentDomain.GetAssemblies().SelectMany(x => x.GetTypes()).Where(x => typeof(IRedpointEOSPlatform).IsAssignableFrom(x) && x.IsClass))
        {
            Console.WriteLine("EOSSDK: Considering platform implementation " + PlatformImplementationType.Name + "...");
            IRedpointEOSPlatform PlatformCandidate = (IRedpointEOSPlatform)Activator.CreateInstance(PlatformImplementationType);
            if (PlatformCandidate.IsActive(Target))
            {
                Console.WriteLine("EOSSDK: Selected platform implementation " + PlatformImplementationType.Name + ".");
                SelectedPlatform = PlatformCandidate;
                break;
            }
        }
        if (SelectedPlatform == null)
        {
            Console.WriteLine("ERROR: The EOS SDK is not supported on this platform. Either update .Build.cs or remove the platform from the WhitelistPlatforms setting in the .uplugin file.");
            throw new Exception("EOS SDK not available for this platform");
        }

        // Determine the platform suffix.
        var PlatformSuffix = SelectedPlatform.GetPlatformSuffix();

        // Locate the SDK.
        string ModuleBase = Module.ModuleDirectory;
        string SdkBase = RedpointEOSSDK.LocateSdkDirectory(Module, Target, ModuleBase, PlatformSuffix, SelectedPlatform.GetSDKVersionConstraints(), out EOSSDKFullVersion);
        if (SdkBase == null)
        {
            Console.WriteLine("ERROR: Could not locate the EOS SDK. Please download it from the Epic Games developer portal and extract it in one of the supported locations.");
            throw new Exception("EOS SDK not found");
        }

        // Wire everything up.
        SelectedPlatform.ConfigureModule(SdkBase, ModuleBase, Module, Target);
    }

    private static string LocateSdkDirectory(ModuleRules Module, ReadOnlyTargetRules Target, string ModuleBase, string PlatformSuffix, RedpointEOSSDKVersionConstraints Constraints, out string EOSSDKFullVersionOut)
    {
        string ForcedSDKVersion = OnlineSubsystemRedpointEOSConfig.GetString(Target, "FORCE_SDK_VERSION" + PlatformSuffix.Replace("-", "_"), "");
        if (string.IsNullOrWhiteSpace(ForcedSDKVersion))
        {
            ForcedSDKVersion = OnlineSubsystemRedpointEOSConfig.GetString(Target, "FORCE_SDK_VERSION", "");
        }

        bool bSearchedAtLeastOneLocation = false;
        bool bIsMaximumTolerableConstrained = Constraints.MaximumTolerableSDKVersion != null;
        List<string> ConstraintWarnings = new List<string>();
        foreach (var EOSSDKFullVersion in EOSSDKSupportedVersions)
        {
            if (!string.IsNullOrWhiteSpace(ForcedSDKVersion))
            {
                if (EOSSDKFullVersion != ForcedSDKVersion)
                {
                    // If the developer is forcing a particular SDK version, only accept that version.
                    continue;
                }
            }

            bSearchedAtLeastOneLocation = true;

            bool bIsThisVersionConstrained = false;
            if (Constraints.MaximumTolerableSDKVersion != null && bIsMaximumTolerableConstrained)
            {
                bIsThisVersionConstrained = true;

                if (Constraints.MaximumTolerableSDKVersion == EOSSDKFullVersion)
                {
                    bIsMaximumTolerableConstrained = false;
                }
            }
            if (Constraints.SDKVersionDenyList != null && Constraints.SDKVersionDenyList.Contains(EOSSDKFullVersion))
            {
                bIsThisVersionConstrained = true;
            }

            string[] CandidateDirectories;
            if (OnlineSubsystemRedpointEOSConfig.GetBool(Target, "FORCE_SDK_USAGE_FROM_PLUGIN", false))
            {
                CandidateDirectories = new string[]
                {
                    // Where the "SDK" folder extracted from the ZIP has been renamed to "ThirdParty" and placed next to "OnlineSubsystemRedpointEOS".
                    Path.Combine(Path.GetFullPath(ModuleBase), "..", "ThirdParty" + PlatformSuffix),
                };
            }
            else if (System.IO.Path.DirectorySeparatorChar == '\\')
            {
                CandidateDirectories = new string[]
                {
                    // Where the "SDK" folder extracted from the ZIP has been renamed to "ThirdParty" and placed next to "OnlineSubsystemRedpointEOS".
                    Path.Combine(Path.GetFullPath(ModuleBase), "..", "ThirdParty" + PlatformSuffix),
                    // Where the SDK has been extracted into the Plugins folder of the project (for developers who want to use the plugin as a Git submodule and still version the SDK).
                    Path.Combine(Path.GetFullPath(ModuleBase), "..", "..", "..", "..", "EOS-SDK" + PlatformSuffix + "-" + EOSSDKFullVersion, "SDK"),
                    // Where the SDK has been extracted into C:\ProgramData\EOS-SDK-<version>\
                    Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData), "EOS-SDK" + PlatformSuffix + "-" + EOSSDKFullVersion, "SDK"),
                    // Where the SDK has been extracted into the user's downloads folder
                    Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Downloads", "EOS-SDK" + PlatformSuffix + "-" + EOSSDKFullVersion, "SDK"),
                    // Where the SDK has been extracted into C:\EOS-SDK-<version>\
                    Path.Combine(Environment.GetEnvironmentVariable("SYSTEMDRIVE"), "EOS-SDK" + PlatformSuffix + "-" + EOSSDKFullVersion, "SDK"),
                };
            }
            else
            {
                CandidateDirectories = new string[]
                {
                    // Where the "SDK" folder extracted from the ZIP has been renamed to "ThirdParty" and placed next to "OnlineSubsystemRedpointEOS".
                    Path.Combine(Path.GetFullPath(ModuleBase), "..", "ThirdParty" + PlatformSuffix),
                    // Where the SDK has been extracted into the Plugins folder of the project (for developers who want to use the plugin as a Git submodule and still version the SDK).
                    Path.Combine(Path.GetFullPath(ModuleBase), "..", "..", "..", "..", "EOS-SDK" + PlatformSuffix + "-" + EOSSDKFullVersion, "SDK"),
                    // Where the SDK has been extracted into the user's downloads folder
                    Path.Combine(Environment.GetEnvironmentVariable("HOME"), "Downloads", "EOS-SDK" + PlatformSuffix + "-" + EOSSDKFullVersion, "SDK"),
                };
            }

            foreach (var Dir in CandidateDirectories)
            {
                if (!bIsThisVersionConstrained)
                {
                    try
                    {
                        Console.WriteLine("EOSSDK: Searching for EOS SDK in path: " + new DirectoryInfo(Dir).FullName);
                    }
                    catch
                    {
                        Console.WriteLine("EOSSDK: Searching for EOS SDK in path: " + Dir);
                    }
                }
                if (Directory.Exists(Dir))
                {
                    if (bIsThisVersionConstrained)
                    {
                        ConstraintWarnings.Add("WARNING: Found EOS SDK, but platform constraints meant that it couldn't be chosen as the SDK for the build. You probably need to install a different version of the SDK. The EOS SDK was found at: " + Dir);
                    }
                    else
                    {
                        Console.WriteLine("EOSSDK: Located EOS SDK at: " + Dir);
                        EOSSDKFullVersionOut = EOSSDKFullVersion;
                        return Dir;
                    }
                }
            }
        }

        foreach (var Warning in ConstraintWarnings)
        {
            Console.WriteLine(Warning);
        }

        if (!bSearchedAtLeastOneLocation)
        {
            Console.WriteLine("ERROR: The ONLINE_SUBSYSTEM_EOS_FORCE_SDK_VERSION is incorrectly set, as it did not match any of the supported EOS SDK versions.");
        }

        EOSSDKFullVersionOut = "";
        return null;
    }
}

