#!/bin/bash

set echo on

mkdir -p ../Linux/bin

cFilenames=$(find . -type f -name "*.c")

assembly="testbed"
compilerFlags="-g -fdeclspec -fPIC"

includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../bin/ -lengine -Wl,-rpath,."
defines="-D_DEBUG -DKEXPORT"

echo "BUILDING [$assembly]..."
echo clang $cFilenames $compilerFlags -o ../Linux/bin/$assembly $defines $includeFlags $linkerFlags
clang $cFilenames $compilerFlags -o ../Linux/bin/$assembly $defines $includeFlags $linkerFlags

