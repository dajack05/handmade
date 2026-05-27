# Handmade Calculator

This isn't a good calculator. But it's mine!

The goal is to remove all STD stuff from it eventually.

Current Libs:
- [Raylib](https://github.com/raysan5/raylib)
- [stb_snprintf](https://github.com/nothings/stb)

## Prerequisites

- [CMake](https://cmake.org/)
- Clang/GCC (or I guess MSVC but I haven't tested that yet)

### MacOS

Builds as-is. Assuming your C++ build system works for other projects, it should work for this.

### Linux

You'll need to install a development libraries for opengl and X11 stuff. The build process will error out and tell you what to install lol

For Debian based systems, when it errors with something like "unable to find xrandr" you can just run `apt install libxrandr-dev`. Keep doing that process until it builds 🤷

### Windows

You're on your own pal... My best guess would be to suggest using something like [msys2](https://www.msys2.org/) or try building the CMake project in Visual Studio.

## Building

This project uses the [meson](https://mesonbuild.com/) build system.

1. Clone/download the repo.
2. Move to the root of the Calc project.
3. Execute `make release`. This will use make to run all the meson commands and build the executable.

