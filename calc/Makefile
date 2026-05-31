all:
	cmake --build build 
	test -f ./build/calc && mv ./build/calc . || true
	test -f ./build/calc.app && mv ./build/calc.app . || true

setup:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

run: all
	./calc

debug: all
	lldb ./calc

clean:
	cmake --build build --target clean

release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=MinSizeRel
	make all

