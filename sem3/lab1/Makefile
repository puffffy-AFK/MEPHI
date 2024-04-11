all: compile test cli

compile:
	cmake -S . -B build
	cd build && make

cli: compile
	./build/cli

test: compile
	./build/tests
	./build/stl_tests

clean:
	rm -rf build
