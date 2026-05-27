all:
	cmake --build build && mv ./build/calc .

setup:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

run: all
	./calc

release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=MinSizeRel
	make all

