all: compile cli

compile:
	cmake -S . -B build
	cd build && make


cli: compile
	./build/cli

clean:
	rm -rf build
