#!/bin/bash
if [[ -d "build"  ]]
then
        /bin/rm -rf ./build
fi

mkdir build
cmake ./ -Bbuild -DTESTING=true

make -C ./build -j16

if [[ -f "build/test/TrashMoverTest" ]]
then
    build/test/TrashMoverTest
fi
