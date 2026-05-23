# Handmade Calculator

This isn't a good calculator. But it's mine!

The goal is to remove all STD stuff from it eventually.

Current Libs:
- [Raylib](https://github.com/raysan5/raylib)
- [stb_snprintf](https://github.com/nothings/stb)

## Building

I use [meson](https://mesonbuild.com/) when developing, but I've also included basic Makefile support.

### If using [Meson](https://mesonbuild.com/)

1. Clone/download the repo.
2. Move to the root of the Calc project.
3. Execute `make release`. This will use make to run all the meson commands and build the executable.

### If using GCC

1. Clone/download the repo.
2. Move to the root of the Calc project.
3. Execute `make nomeson`. This will compile a release build using G++.
