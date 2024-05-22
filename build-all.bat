@ECHO OFF 
REM

ECHO "BUILDING EVERYTHING..."

PUSHD engine
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD testbed
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

set version=0.0.1-dev

ECHO "ALL ASSEMBLIES BUILT SUCCESSFULLY."
echo "Compressing Source Code and Build"
tar -zcvf build_and_source_%version%.tar.gz * 