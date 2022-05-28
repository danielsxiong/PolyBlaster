@echo off
echo UAT: Locating MSBuild...
call "GetMSBuildPath.bat"
echo UAT: Switching to correct build directory...
cd ../../
echo UAT: Restoring AutomationTool packages... (UE5)
%MSBUILD_EXE% /nologo /verbosity:quiet Source\Programs\AutomationTool\Scripts\AutomationScripts.Automation.csproj /property:Configuration=Development /property:Platform=AnyCPU /t:Restore "/property:OutputPath=%ENGINE_PATH%\Engine\Binaries\DotNET_EOSPatched" "/property:ReferencePath=%ENGINE_PATH%\Engine\Binaries\DotNET\AutomationScripts"
echo UAT: Building AutomationTool binary... (UE5)
%MSBUILD_EXE% /nologo /verbosity:quiet Source\Programs\AutomationTool\Scripts\AutomationScripts.Automation.csproj /property:Configuration=Development /property:Platform=AnyCPU "/property:OutputPath=%ENGINE_PATH%\Engine\Binaries\DotNET_EOSPatched" "/property:ReferencePath=%ENGINE_PATH%\Engine\Binaries\DotNET\AutomationScripts"