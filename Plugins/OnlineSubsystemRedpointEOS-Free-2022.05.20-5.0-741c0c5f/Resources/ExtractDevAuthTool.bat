@echo off
echo Extracting Developer Authentication Tool from the SDK...
echo Located in: %*
cd %*
powershell -command Expand-Archive -Verbose EOS_DevAuthTool-win32-x64-1.0.1.zip EOS_DevAuthTool-win32-x64-1.0.1