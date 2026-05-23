all:
	meson compile -C build && mv ./build/calc .

setup:
	meson setup --reconfigure ./build

run: all
	./calc

release:
	meson setup --buildtype=release ./build
	meson compile -C build && mv ./build/calc .

SRC := 	src/main.cpp 					\
  			src/Layout.cpp 				\
  			src/ViewFuncs.cpp 		\
  			src/Stats.cpp 				\
  			src/Calc.cpp 					\
  			src/util/String.cpp 	\
  			src/lib/stb_sprintf.c \

LIB := -lraylib
nomeson:
	g++ -O3 -DNDEBUG ${SRC} ${LIB} -I./ -o calc
