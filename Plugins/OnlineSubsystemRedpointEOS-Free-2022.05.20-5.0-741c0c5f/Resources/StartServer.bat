@echo off
rem This script makes it simple to launch EAC protected game servers, and to get the log output from the server to display in the Command Prompt.
cd %~dp0
powershell -ExecutionPolicy Bypass .\StartServer.ps1 %*