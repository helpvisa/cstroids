OUTPUT=cstroids

main: assemble
	cc -Wall ./build/*.o -o ./$(OUTPUT) -lSDL2 -lm

assemble:
	mkdir -p ./build
	cc -Wall -c ./src/wrap_sdl/draw.c -o ./build/draw.o
	cc -Wall -c ./src/wrap_sdl/init.c -o ./build/init.o
	cc -Wall -c ./src/wrap_sdl/input.c -o ./build/input.o
	cc -Wall -c ./src/objects/particle.c -o ./build/particle.o
	cc -Wall -c ./src/objects/asteroid.c -o ./build/asteroid.o
	cc -Wall -c ./src/objects/ship.c -o ./build/ship.o
	cc -Wall -c ./src/globals.c -o ./build/globals.o
	cc -Wall -c ./src/rng.c -o ./build/rng.o
	cc -Wall -c ./src/main.c -o ./build/main.o

clean:
	rm -rf ./build
