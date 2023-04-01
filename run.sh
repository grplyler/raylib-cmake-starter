#!/bin/bash

export ANGLE_LIBRARY_PATH=/Users/ryan/code/projects/raylib-cmake-starter/vendor/angle/out/Release
export DYLD_LIBRARY_PATH=${ANGLE_LIBRARY_PATH}:${DYLD_LIBRARY_PATH}

./build/raylib-starter