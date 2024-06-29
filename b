#!/bin/bash

cmake -B build
cmake --build build

# if $1 == "angle"

if [ "$1" == "angle" ]; then
    cmake -DCUSTOMIZE_BUILD=ON -DUSE_ANGLE=ON -DOPENGL_VERSION="ES 2.0" -B build_angle
    cmake --build build_angle
else
    cmake -B build
    cmake --build build
fi