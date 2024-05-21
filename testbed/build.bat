REM BUILD SCRIPT for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f
)

REM

SET assembly=testbed
SET compilerFlags=-g
REM
SET includeFlags=-Isrc -I../engine/src/
SET linkerFlags=-L../bin/ -lengine.lib 
SET defines=-D_DEBUG -DKIMPORT

ECHO "BUILDING [%assembly%]..."
clang %cFilenames% %compilerFlags% -o ../Windows/bin/%assembly%.exe %defines% %includeFlags% %linkerFlags%