main: assemble
	cc -Wall -O2 -o ./sdl-bin ./build/*.o -lSDL2

assemble:
	mkdir -p ./build/
	cc -Wall -c ./*.c
	mv ./*.o ./build/
