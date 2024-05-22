#!/bin/bash
# Build script for testbed
set echo on

mkdir -p ../Linux/bin

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.c")

# echo "Files:" $cFilenames

assembly="testbed"
compilerFlags="-g -fdeclspec -fPIC" 
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../Linux/bin/ -lengine -Wl,-rpath,."
defines="-D_DEBUG -DKIMPORT"

echo "Building $assembly..."
echo clang $cFilenames $compilerFlags -o ../Linux/bin/$assembly $defines $includeFlags $linkerFlags
clang $cFilenames $compilerFlags -o ../Linux/bin/$assembly $defines $includeFlags $linkerFlags