# Handmade Calculator

This isn't a good calculator. But it's mine!

The goal is to remove all STD stuff from it eventually.

Current Libs:
- [Raylib](https://github.com/raysan5/raylib)
- [stb_snprintf](https://github.com/nothings/stb)

## Prerequisites

- [CMake](https://cmake.org/)
- Clang/GCC (or I guess MSVC but I haven't tested that yet)

## Building

This project uses the [cmake](https://cmake.org/) build system.

For ease of development I've also made a Makefile that handles some of the gruntwork.

You can look through the Makefile and see what they do. It's hardcoded to use tools like LLDB for debugging.

**For most regular builds**

1. Clone/download the repo.
2. Move to the root of the Calc project.
3. Execute `make release`.
4. Profit.

That's pretty much it. You should be left with a single executable in the calc directory.
