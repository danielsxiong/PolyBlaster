#
# This script is used to sign projects for Anti-Cheat on Windows.
#
param([string] $EngineDir, [string] $ProjectDir, [string] $PluginDir, [string] $StageDir)

$ErrorActionPreference = "Stop"

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

$TargetPlatform = $env:TargetPlatform
$TargetConfiguration = $env:TargetConfiguration

if ($TargetPlatform -ne "Win64") {
    # We don't sign for this target platform.
    exit 0
}

$AntiCheatEnabled = $false
$ProductId = $null
$SandboxId = $null
$DeploymentId = $null
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
            if ($ConfigLine.StartsWith("SandboxId=")) {
                $SandboxId = $ConfigLine.Substring("SandboxId=".Length).Trim()
            }
            if ($ConfigLine.StartsWith("DeploymentId=")) {
                $DeploymentId = $ConfigLine.Substring("DeploymentId=".Length).Trim()
            }
        }
    }
}
if ($ProductId -eq $null -or $SandboxId -eq $null -or $DeploymentId -eq $null -or !$AntiCheatEnabled) {
    # Anti-Cheat or EOS not enabled for this project.
    exit 0
}

if (!(Test-Path "$ProjectDir\Build\NoRedist\base_private.key")) {
    Write-Host "error: Missing Build\NoRedist\base_private.key for Anti-Cheat signing. Either download the file and place it there, or turn off Anti-Cheat in Project Settings."
    exit 1
}
if (!(Test-Path "$ProjectDir\Build\NoRedist\base_public.cer")) {
    Write-Host "error: Missing Build\NoRedist\base_public.cer for Anti-Cheat signing. Either download the file and place it there, or turn off Anti-Cheat in Project Settings."
    exit 1
}

Write-Host "Signing project for Anti-Cheat..."
Write-Host "Engine path: $EngineDir"
Write-Host "Plugin dir: $PluginDir"
Write-Host "Project dir: $ProjectDir"
Write-Host "Stage dir: $StageDir"
Write-Host "Target platform: $TargetPlatform"
Write-Host "Target configuration: $TargetConfiguration"
Write-Host "EOS product ID: $ProductId"

$SdkLocation = $null
$SdkVersions = @(
    "18950192-v1.14.2-hf-1",
    "18843384-v1.14.2",
    "18153445-v1.14.1",
    "18059966-v1.14.1",
    "17607641-v1.14",
    "16972539-v1.13.1",
    "16697186-v1.13",
    "16488214-v1.12"
)
foreach ($SdkVersion in $SdkVersions) {
    $SdkLocations = @(
        "$PluginDir\Source\ThirdParty",
        "$ProjectDir\Plugins\EOS-SDK-$SdkVersion\SDK",
        "$env:PROGRAMDATA\EOS-SDK-$SdkVersion\SDK",
        "$env:USERPROFILE\Downloads\EOS-SDK-$SdkVersion\SDK",
        "$env:SYSTEMDRIVE\EOS-SDK-$SdkVersion\SDK"
    )
    foreach ($CandidateLocation in $SdkLocations) {
        if (Test-Path $CandidateLocation) {
            $SdkLocation = $CandidateLocation
            break
        }
    }
    if ($SdkLocation -ne $null) {
        break
    }
}
if ($SdkLocation -eq $null) {
    Write-Host "error: Could not find EOS SDK in any installed location for Anti-Cheat signing."
    exit 1
}

$AntiCheatVersions = @(
    "EOS_AntiCheatTools-win32-x64-1.2.2",
    "EOS_AntiCheatTools-win32-x64-1.2.1",
    "EOS_AntiCheatTools-win32-x64-1.2.0",
    "EOS_AntiCheatTools-win32-x64-1.1.2"
)
$AntiCheatVersion = ""
$AntiCheatNeedsGameDirectory = $true

foreach ($CandidateVersion in $AntiCheatVersions) {
    if (!(Test-Path "$SdkLocation\Tools\$CandidateVersion")) {
        if (!(Test-Path "$SdkLocation\Tools\$CandidateVersion.zip")) {
            continue
        }

        Write-Host "Extracting tools for Anti-Cheat signing..."
        Expand-Archive "$SdkLocation\Tools\$CandidateVersion.zip" "$SdkLocation\Tools\$CandidateVersion"
    }
    $AntiCheatVersion = $CandidateVersion
    if ($AntiCheatVersion -eq "EOS_AntiCheatTools-win32-x64-1.1.2") {
        $AntiCheatNeedsGameDirectory = $false
    }
    Write-Host "Using Anti-Cheat Tools version: $AntiCheatVersion"
    break
}
if ($AntiCheatVersion -eq "") {
    Write-Host "error: Could not find Anti-Cheat tools for Anti-Cheat signing."
    exit 1
}

$WorkingDirectoryEntry = ""
if (!$AntiCheatNeedsGameDirectory) {
    $WorkingDirectoryEntry = "working_directory = `"$StageDir`";"
}
$AntiCheatConfig = @"
config_info:
{
    version = 2;
};
search_options:
{
    $WorkingDirectoryEntry
    exclude_size_threshold = 0;
    exclude_paths = [
        "EasyAntiCheat\\Certificates",
        "EasyAntiCheat\\Licenses"
    ];
    exclude_extensions = [
        ".bak",
        ".bat",
        ".bmp",
        ".cfg",
        ".db",
        ".ico",
        ".inf",
        ".ini",
        ".jpg",
        ".last",
        ".log",
        ".manifest",
        ".mdb",
        ".pdb",
        ".png",
        ".pubkey",
        ".txt",
        ".vdf",
        ".xml"
    ];
    ignore_files_without_extension = false;
};
"@
Set-Content -Path "$ProjectDir\Saved\anticheat_integritytool.cfg" -Value $AntiCheatConfig

if ($AntiCheatNeedsGameDirectory) {
    & "$SdkLocation\Tools\$AntiCheatVersion\devtools\anticheat_integritytool64.exe" -productid $ProductId -inkey "$ProjectDir\Build\NoRedist\base_private.key" -incert "$ProjectDir\Build\NoRedist\base_public.cer" -target_game_dir "$StageDir" "$ProjectDir\Saved\anticheat_integritytool.cfg"
} else {
    & "$SdkLocation\Tools\$AntiCheatVersion\devtools\anticheat_integritytool64.exe" -productid $ProductId -inkey "$ProjectDir\Build\NoRedist\base_private.key" -incert "$ProjectDir\Build\NoRedist\base_public.cer" "$ProjectDir\Saved\anticheat_integritytool.cfg"
}
if ($LASTEXITCODE -ne 0) {
    Write-Host "error: Anti-Cheat integrity tool failed to run successfully."
    exit $LASTEXITCODE
}

# Determine executable name.
$ExecutableName = $null
$IsServer = $false
foreach ($Exe in (Get-ChildItem -Path $StageDir -Filter *.exe)) {
    if ($Exe.Name -ne "start_protected_game.exe") {
        $ExecutableName = $Exe.Name.Substring(0, $Exe.Name.Length - 4)
        if ($ExecutableName.EndsWith("Server")) {
            $IsServer = $true
        }
        break
    }
}

# Determine folder name.
$FolderName = $null
foreach ($Folder in (Get-ChildItem -Path $StageDir -Directory)) {
    if ($Folder.Name -ne "Engine" -and $Folder.Name -ne "EasyAntiCheat") {
        $FolderName = $Folder.Name
        break
    }
}

# Check that we could figure out the executable name and folder name.
if ($ExecutableName -eq $null -or $FolderName -eq $null) {
    Write-Host "error: Anti-Cheat could not determine project name from main executable filename."
    exit 1
}

# Determine main executable path.
$MainExePath = $null
foreach ($Exe in (Get-ChildItem -Path "$StageDir\$FolderName\Binaries\Win64" -Filter *.exe)) {
    if ($Exe.Name.StartsWith("$ExecutableName")) {
        $MainExePath = $Exe.FullName

        # Copy client module if this is *not* a Shipping build. Client module override is only used for testing.
        if ((Test-Path "$ProjectDir\Build\NoRedist\game.exe.eac") -and $TargetConfiguration -ne "Shipping") {
            Copy-Item -Force "$ProjectDir\Build\NoRedist\game.exe.eac" "$($Exe.FullName).eac"
        }
    }
}
if ($MainExePath -eq $null) {
    Write-Host "error: Could not determine main executable for Anti-Cheat to run."
}
$RelativeExePath = $MainExePath.Substring($StageDir.Length+1)
$RelativeExePathEscaped = $RelativeExePath.Replace("\", "\\")

# Now copy runtime dependencies.
$ServerMode = "0"
if ($IsServer) {
    $ServerMode = "1"
}
Copy-Item -Force -Recurse "$SdkLocation\Tools\$AntiCheatVersion\dist\*" "$StageDir\"
Set-RetryableContent -Path "$StageDir\EasyAntiCheat\Settings.json" -Value @"
{
	"productid"										: "$ProductId",
	"sandboxid"										: "$SandboxId",
	"deploymentid"									: "$DeploymentId",
	"title"											: "$ExecutableName",
	"executable"									: "$RelativeExePathEscaped",
	"logo_position"									: "bottom-left",
	"parameters"									: "",
	"use_cmdline_parameters"						: "1",
	"working_directory"								: "",
	"wait_for_game_process_exit"					: "$ServerMode",
	"hide_splash_screen"							: "$ServerMode",
	"hide_ui_controls"								: "$ServerMode"
}
"@

# Remove launch executable that can't be used.
Remove-Item -Force "$StageDir\$ExecutableName.exe"

# Rename start_protected_game.exe so it has the name of the original game. This keeps games compatible with
# any launch scripts the developer might have written before enabling Anti-Cheat.
Move-Item -Force "$StageDir\start_protected_game.exe" "$StageDir\$ExecutableName.exe"

# If the developer has specified an Anti-Cheat splash screen inside Build\NoRedist, use that instead.
if (Test-Path "$ProjectDir\Build\NoRedist\AntiCheatSplashScreen.png") {
    Copy-Item -Force "$ProjectDir\Build\NoRedist\AntiCheatSplashScreen.png" "$StageDir\EasyAntiCheat\SplashScreen.png"
}

# Create batch scripts to install/uninstall Anti-Cheat.
Set-RetryableContent -Path "$StageDir\InstallAntiCheat.bat" -Value @"
@echo off
cd %~dp0
EasyAntiCheat\EasyAntiCheat_EOS_Setup.exe install $ProductId
"@
Set-RetryableContent -Path "$StageDir\UninstallAntiCheat.bat" -Value @"
@echo off
cd %~dp0
EasyAntiCheat\EasyAntiCheat_EOS_Setup.exe uninstall $ProductId
"@

# If this is a dedicated server, add some scripts that make it easier to get the logs.
if ($IsServer) {
    Copy-Item -Force "$PluginDir\Resources\StartServer.bat" "$StageDir\StartServer.bat"
    Copy-Item -Force "$PluginDir\Resources\StartServer.ps1" "$StageDir\StartServer.ps1"
}

exit 0