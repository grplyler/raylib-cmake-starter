# Raylib CMake Starter for C++

This is a starter project for using [Raylib](https://www.raylib.com/) with C++ and CMake.
**WARNING: Only tested on MacOS**


## Getting Started

1. Clone this repository
2. Initialize the submodules: `git submodule update --init --recursive`
3. Build `./b`
4. Run `./r`

## Building with Google ANGLE (10x more draw calls on Apple Silicon) (Only tested on MacOS)

1. Grab ANGLE Dylibs from Your Google Chrome Installation

```
cd /Applications/Google\ Chrome.app
find ./ -name libGLESv2.dylib
find ./ -name libEGL.dylib
```

2. Copy the Dylibs to `libs/`

3. Build with ANGLE `./b angle`

## TODO

- [x] Support for ANGLE
- [ ] Support more Platforms
- [ ] Add ENet for Networking 