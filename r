#!/bin/bash

if [ "$1" == "angle" ]; then
    export DYLD_LIBRARY_PATH=libs/
    ./build_angle/raylib-starter
else

    ./build/raylib-starter
fi
