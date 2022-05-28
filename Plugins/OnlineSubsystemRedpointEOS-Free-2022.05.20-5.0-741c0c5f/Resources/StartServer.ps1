#
# This script simplifies launching EAC protected servers and getting the log output in the Command Prompt.
#
param()

$ErrorActionPreference = "Stop"

$MainExecutable = (Get-ChildItem $PSScriptRoot -Filter *.exe)[0]
$ProjectName = $MainExecutable.Name.Substring(0, $MainExecutable.Name.Length - "Server.exe".Length)
Write-Host "Launching $ProjectName using executable $MainExecutable..."

$CanMonitorEAC = $true
$EACLogPath = "$env:APPDATA\EasyAntiCheat\gamelauncher.log"
if (Test-Path $EACLogPath) {
    try {
        Remove-Item -Force $EACLogPath
    } catch {
        $CanMonitorEAC = $false
    }
}
$ServerLogPath = "$PSScriptRoot\$ProjectName\Saved\Logs\$ProjectName.log"
if (Test-Path $ServerLogPath) {
    Remove-Item -Force $ServerLogPath
}

$EACLogHandle = $null
$ServerLogHandle = $null

$ArgList = @("-stdlog")
if ($args -ne $null -and $args.Length -gt 0) {
    $ArgList = $args
}
$Process = Start-Process -FilePath $MainExecutable.FullName -PassThru -ArgumentList $ArgList
if ($Process -eq $null) {
    Write-Error "Unable to start server process!"
    exit 1
}
$SleepTime = 50
try {
    while (!$Process.HasExited) {
        if (!(Test-Path $ServerLogPath)) {
            if (!(Test-Path $EACLogPath)) {
                Write-Host "Waiting for EAC Launcher or Unreal Engine to start logging..."
                Start-Sleep -Milliseconds 500
                continue
            }

            if ($CanMonitorEAC) {
                if ($EACLogHandle -eq $null) {
                    # Open the log file for reading.
                    $EACLogHandle = [System.IO.File]::Open($EACLogPath, [System.IO.FileMode]::Open, [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite -bor [System.IO.FileShare]::Delete)
                }
                $NumToRead = $EACLogHandle.Length - $EACLogHandle.Position
                $NumRead = 0
                if ($NumToRead -gt 0) {
                    $ByteArray = [System.Byte[]]::CreateInstance([System.Byte], $NumToRead)
                    $NumRead = $EACLogHandle.Read($ByteArray, 0, $NumToRead)
                }
                if ($NumRead -gt 0) {
                    $LogContent = [System.Text.Encoding]::UTF8.GetString($ByteArray, 0, $NumRead)
                    Write-Host -NoNewLine $LogContent
                    $SleepTime = 50
                } else {
                    $SleepTime = $SleepTime * 2
                    if ($SleepTime -gt 1000) {
                        $SleepTime = 1000
                    }
                }
            } else {
                $SleepTime = 1000
            }
            Start-Sleep -Milliseconds $SleepTime
            $Process.Refresh()
        } else {
            if ($EACLogHandle -ne $null) {
                # Read rest of EAC file before reading server log.
                $NumToRead = $EACLogHandle.Length - $EACLogHandle.Position
                $ByteArray = [System.Byte[]]::CreateInstance([System.Byte], $NumToRead)
                $NumRead = $EACLogHandle.Read($ByteArray, 0, $NumToRead)
                if ($NumRead -gt 0) {
                    $LogContent = [System.Text.Encoding]::UTF8.GetString($ByteArray, 0, $NumRead)
                    Write-Host -NoNewLine $LogContent
                }
                $EACLogHandle.Close()
                $EACLogHandle = $null
            }
            if ($ServerLogHandle -eq $null) {
                # Open the log file for reading.
                $ServerLogHandle = [System.IO.File]::Open($ServerLogPath, [System.IO.FileMode]::Open, [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite -bor [System.IO.FileShare]::Delete)
            }
            $NumToRead = $ServerLogHandle.Length - $ServerLogHandle.Position
            $NumRead = 0
            if ($NumToRead -gt 0) {
                $ByteArray = [System.Byte[]]::CreateInstance([System.Byte], $NumToRead)
                $NumRead = $ServerLogHandle.Read($ByteArray, 0, $NumToRead)
            }
            if ($NumRead -gt 0) {
                $LogContent = [System.Text.Encoding]::UTF8.GetString($ByteArray, 0, $NumRead)
                Write-Host -NoNewLine $LogContent
                $SleepTime = 50
            } else {
                $SleepTime = $SleepTime * 2
                if ($SleepTime -gt 1000) {
                    $SleepTime = 1000
                }
            }
            Start-Sleep -Milliseconds $SleepTime
            $Process.Refresh()
        }
    }
} finally {
    if (!$Process.HasExited) {
        # Ensure we kill the process if the user Ctrl-C's the script.
        Write-Host "Killing server process..."
        function Kill-Tree {
            Param([int]$ppid)
            Get-CimInstance Win32_Process | Where-Object { $_.ParentProcessId -eq $ppid } | ForEach-Object { Kill-Tree $_.ProcessId }
            Stop-Process -Id $ppid
        }
        Kill-Tree $Process.Id
    }
}

exit $Process.ExitCode