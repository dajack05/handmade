all:
	meson compile -C build && mv ./build/calc .

setup:
	meson setup --reconfigure ./build

run: all
	./calc
