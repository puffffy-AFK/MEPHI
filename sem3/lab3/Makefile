all: compile alphabet histogram tic-tac-toe

compile:
	cmake -S . -B build
	cd build && make

histogram: compile
	./build/histogram

alphabet: compile
	./build/alphabet

tic-tac-toe: compile
	./build/tic_tac_toe

clean:
	rm -rf build
