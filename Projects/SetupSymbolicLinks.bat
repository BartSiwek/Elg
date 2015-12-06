@echo off

IF NOT EXIST Elg/Source (
  ECHO Creating symbolic link to Elg source
  MKLINK /j "Elg/Source" "../Src/Elg"
) ELSE (
  ECHO Skipping creation of symbolic link to Elg source
)

IF NOT EXIST Elg.DirectX/Source (
  ECHO Creating symbolic link to Elg.DirectX source
  MKLINK /j "Elg.DirectX/Source" "../Src/Elg.DirectX"
) ELSE (
  ECHO Skipping creation of symbolic link to Elg.DirectX source
)

IF NOT EXIST Elg.DirectX.Tests/Source (
  ECHO Creating symbolic link to Elg.DirectX.Tests source
  MKLINK /j "Elg.DirectX.Tests/Source" "../Src/Elg.DirectX.Tests"
) ELSE (
  ECHO Skipping creation of symbolic link to Elg.DirectX.Tests source
)

IF NOT EXIST Demos/Elg.Demos.BasicDirectX/Source (
  ECHO Creating symbolic link to Elg.Demos.BasicDirectX source
  MKLINK /j "Demos/Elg.Demos.BasicDirectX/Source" "../Src/Demos/Elg.Demos.BasicDirectX"
) ELSE (
  ECHO Skipping creation of symbolic link to Elg.Demos.BasicDirectX source
)

IF NOT EXIST Elg.Tests/Source (
  ECHO Creating symbolic link to Elg.Tests source
  MKLINK /j "Elg.Tests/Source" "../Src/Elg.Tests"
) ELSE (
  ECHO Skipping creation of symbolic link to Elg.Tests source
)

pause
exit /b 0
