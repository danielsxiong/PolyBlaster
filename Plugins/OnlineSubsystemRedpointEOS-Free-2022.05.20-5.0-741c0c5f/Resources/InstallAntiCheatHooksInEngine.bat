@echo off
"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -ExecutionPolicy Bypass -File "%~dp0\InstallAntiCheatHooksInEngine.ps1" -ProjectDir %1
exit %errorlevel%