# Handmade Calculator

This isn't a good calculator. But it's mine!

The goal is to remove all STD stuff from it eventually.

Current Libs:
- [Raylib](https://github.com/raysan5/raylib)
- [stb_snprintf](https://github.com/nothings/stb)

## Prerequisites

- [CMake](https://cmake.org/)
- [Meson](https://mesonbuild.com/)
- [Ninja Build](https://ninja-build.org/)
- Clang/GCC (or I guess MSVC but I haven't tested that yet)

## Building

This project uses the [meson](https://mesonbuild.com/) build system.

1. Clone/download the repo.
2. Populate the raylib submodule via `git submodule update --init --recursive`.
3. Move to the root of the Calc project.
4. Execute `make release`. This will use make to run all the meson commands and build the executable.

