#
# This script patches AutomationTool so that we can run scripts post-stage from a plugin.
#
param([Parameter(Mandatory=$false)][string] $ProjectDir)

$ErrorActionPreference = "Stop"

# Unreal Engine 5 messes up the PATH environment variable. Ensure we fix up PATH from the
# current system's settings.
$UserPath = ([System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::User))
$ComputerPath = ([System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine))
if ($UserPath.Trim() -ne "") {
    $env:PATH = "$($UserPath);$($ComputerPath)"
} else {
    $env:PATH = $ComputerPath
}

# Check to see if the project has Anti-Cheat enabled. If it doesn't, we don't install hooks.
if ($ProjectDir -eq $null -or $ProjectDir -eq "") {
    exit 0
}
$AntiCheatEnabled = $false
$ProductId = $null
$ConfigFile = "$ProjectDir\Config\DefaultEngine.ini"
if (Test-Path $ConfigFile) {
    $ConfigValues = Get-Content $ConfigFile
    $ConfigSection = ""
    foreach ($ConfigLine in $ConfigValues) {
        if ($ConfigLine.StartsWith("[")) {
            $ConfigSection = $ConfigLine.Substring(1, $ConfigLine.Length - 2).Trim()
        }
        if ($ConfigSection -eq "EpicOnlineServices") {
            if ($ConfigLine -eq "EnableAntiCheat=True") {
                $AntiCheatEnabled = $true
            }
            if ($ConfigLine.StartsWith("ProductId=")) {
                $ProductId = $ConfigLine.Substring("ProductId=".Length).Trim()
            }
        }
    }
}
if ($ProductId -eq $null -or !$AntiCheatEnabled) {
    # Anti-Cheat or EOS not enabled for this project.
    exit 0
}

function Set-RetryableContent([string] $Path, [string] $Value) {
    while ($true) {
        try {
            Set-Content -Force -Path $Path -Value $Value
            break
        } catch {
            if ($_.ToString().Contains("Stream was not readable.")) {
                continue
            }
        }
    }
}

# Check to see if the project's post-stage hook is set up correctly.
function Copy-IfNotChanged([string] $SourcePath, [string] $TargetPath) {
    $SourceContent = Get-Content -Raw $SourcePath
    if (Test-Path $TargetPath) {
        $TargetContent = Get-Content -Raw $TargetPath
        if ($SourceContent -eq $TargetContent) {
            return;
        }
    }
    if (!(Test-Path (Resolve-Path "$TargetPath\.."))) {
        New-Item -ItemType Directory (Resolve-Path "$TargetPath\..")
    }
    Write-Host "Setting up $TargetPath..."
    Set-RetryableContent -Path $TargetPath -Value $SourceContent
}
if ($ProjectDir -ne $null -and $ProjectDir -ne "") {
    Copy-IfNotChanged "$PSScriptRoot\PostStageHook.bat" "$ProjectDir\Build\NoRedist\PostStageHook.bat"
    Copy-IfNotChanged "$PSScriptRoot\PostStageHook.ps1" "$ProjectDir\Build\NoRedist\PostStageHook.ps1"
}

# Check to see if CopyBuildToStagingDirectory.Automation.cs is patched in the engine. If it isn't, 
# we need to patch AutomationTool and recompile it so we have a hook that we can use to modify the 
# project when it is staged (not when it's built, which is when we are running right now).
$EngineDir = (Resolve-Path "$((Get-Location).Path)\..\..").Path
$IsUnrealEngine5 = $false
if (Test-Path "$EngineDir\Engine\Binaries\Win64\UnrealEditor-Cmd.exe") {
    $IsUnrealEngine5 = $true
}
$CopyBuildScriptPath = "$EngineDir\Engine\Source\Programs\AutomationTool\Scripts\CopyBuildToStagingDirectory.Automation.cs"
$CopyBuildScriptBackupPath = "$EngineDir\Engine\Source\Programs\AutomationTool\Scripts\CopyBuildToStagingDirectory.Automation.cs.backup"
$CopyBuildScriptContent = Get-Content -Raw $CopyBuildScriptPath
$CopyBuildScriptContentOriginal = $CopyBuildScriptContent
if (!$CopyBuildScriptContent.Contains("// EOS Online Subsystem Anti-Cheat Hook 1.1")) {
    Write-Host "Installing Anti-Cheat staging hooks into AutomationTool..."

    Get-ChildItem -Path "$EngineDir\Engine\Source\Programs\AutomationTool" -Recurse -Filter "*" | % {
        if ($_.IsReadOnly) {
            $_.IsReadOnly = $false
        }
    }
    Get-ChildItem -Path "$EngineDir\Engine\Source\Programs\DotNETCommon" -Recurse -Filter "*" | % {
        if ($_.IsReadOnly) {
            $_.IsReadOnly = $false
        }
    }
    Get-ChildItem -Path "$EngineDir\Engine\Source\Programs\UnrealBuildTool" -Recurse -Filter "*" | % {
        if ($_.IsReadOnly) {
            $_.IsReadOnly = $false
        }
    }

    if (Test-Path $CopyBuildScriptBackupPath) {
        # We previously installed an older hook. Use original to so we can re-patch.
        $CopyBuildScriptContent = Get-Content -Raw $CopyBuildScriptBackupPath
    }

    $Hook = @"
// EOS Online Subsystem Anti-Cheat Hook 1.1
// EOS BEGIN HOOK
private static void ExecuteProjectPostStageHook(ProjectParams Params, DeploymentContext SC)
{
    string StageHookPath = Path.Combine(SC.ProjectRoot.FullName, "Build", "NoRedist", "PostStageHook.bat");
    if (File.Exists(StageHookPath))
    {
        RunAndLog(CmdEnv, StageHookPath, "\"" + SC.StageDirectory + "\"", Options: ERunOptions.Default | ERunOptions.UTF8Output, EnvVars: new Dictionary<string, string>
        {
            { "TargetConfiguration", SC.StageTargetConfigurations.FirstOrDefault().ToString() },
            { "TargetPlatform", SC.StageTargetPlatform.PlatformType.ToString() },
        });
    }
}
// EOS END HOOK
"@
    $CopyBuildScriptContent = $CopyBuildScriptContent.Replace("public static void CopyBuildToStagingDirectory(", "$Hook`r`n`r`npublic static void CopyBuildToStagingDirectory(");
    $CopyBuildScriptContent = $CopyBuildScriptContent.Replace("ApplyStagingManifest(ParamsInstance, SC);", "ApplyStagingManifest(ParamsInstance, SC); ExecuteProjectPostStageHook(ParamsInstance, SC);");
    $CopyBuildScriptContent = $CopyBuildScriptContent.Replace("ApplyStagingManifest(Params, SC);", "ApplyStagingManifest(Params, SC); ExecuteProjectPostStageHook(Params, SC);");
    if (!(Test-Path $CopyBuildScriptBackupPath)) {
        Copy-Item -Force $CopyBuildScriptPath $CopyBuildScriptBackupPath
    }
    Set-RetryableContent -Path $CopyBuildScriptPath -Value $CopyBuildScriptContent

    $Success = $false
    Push-Location "$EngineDir\Engine\Build\BatchFiles"
    try {
        $env:ENGINE_PATH = $EngineDir
        if ($IsUnrealEngine5) {
            & "$PSScriptRoot\ForceRebuildUAT_UE5.bat"
        } else {
            & "$PSScriptRoot\ForceRebuildUAT.bat"
        }
        if ($LASTEXITCODE -ne 0) {
            exit $LASTEXITCODE
        }
        if ($IsUnrealEngine5) {
            Move-Item -Force "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.dll" "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.dll.old"
            Move-Item -Force "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.pdb" "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.pdb.old"
            Copy-Item -Force "$EngineDir\Engine\Binaries\DotNET_EOSPatched\AutomationScripts.Automation.dll" "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.dll"
            Copy-Item -Force "$EngineDir\Engine\Binaries\DotNET_EOSPatched\AutomationScripts.Automation.pdb" "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.pdb"
        } else {
            Move-Item -Force "$EngineDir\Engine\Binaries\DotNET\AutomationScripts\AutomationScripts.Automation.dll" "$EngineDir\Engine\Binaries\DotNET\AutomationScripts\AutomationScripts.Automation.dll.old"
            Move-Item -Force "$EngineDir\Engine\Binaries\DotNET\AutomationScripts\AutomationScripts.Automation.pdb" "$EngineDir\Engine\Binaries\DotNET\AutomationScripts\AutomationScripts.Automation.pdb.old"
            Copy-Item -Force "$EngineDir\Engine\Binaries\DotNET_EOSPatched\AutomationScripts.Automation.dll" "$EngineDir\Engine\Binaries\DotNET\AutomationScripts\AutomationScripts.Automation.dll"
            Copy-Item -Force "$EngineDir\Engine\Binaries\DotNET_EOSPatched\AutomationScripts.Automation.pdb" "$EngineDir\Engine\Binaries\DotNET\AutomationScripts\AutomationScripts.Automation.pdb"
        }
        $Success = $true
    } finally {
        if (!$Success) {
            # Restore original script.
            Set-RetryableContent -Path $CopyBuildScriptPath -Value $CopyBuildScriptContentOriginal
        }
        Pop-Location
    }

    Write-Host "warning: EOS Online Subsystem had to patch your engine's CopyBuildToStagingDirectory.Automation.cs file to be compatible with Anti-Cheat. Executables won't be signed for Anti-Cheat until you next run the build and package the project."
    exit 0
}

exit 0