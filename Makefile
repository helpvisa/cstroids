main: assemble
	cc -Wall -O2 -o ./sdl-bin ./build/*.o -lSDL2

assemble:
	mkdir -p ./build/
	cc -Wall -c ./src/*.c
	cc -Wall -c ./src/wrap_sdl/*.c
	cc -Wall -c ./src/objects/*.c
	mv ./*.o ./build/
