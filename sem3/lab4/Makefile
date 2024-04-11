all: compile main

compile:
	cmake -S . -B build
	cd build && make

main: compile
	./build/main

clean:
	rm -rf build
