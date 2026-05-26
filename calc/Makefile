all:
	cmake --build build && mv ./build/calc .

setup:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

run: all
	./calc

release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=MinSizeRel
	make all

