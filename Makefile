OUTPUT=cstroids
CC=cc

main: assemble
	cc -Wall ./build/*.o -o ./$(OUTPUT) -lSDL2 -lm

assemble:
	mkdir -p ./build
	$(CC) -Wall -c ./src/wrap_sdl/draw.c -o ./build/draw.o
	$(CC) -Wall -c ./src/wrap_sdl/init.c -o ./build/init.o
	$(CC) -Wall -c ./src/wrap_sdl/input.c -o ./build/input.o
	$(CC) -Wall -c ./src/objects/particle.c -o ./build/particle.o
	$(CC) -Wall -c ./src/objects/asteroid.c -o ./build/asteroid.o
	$(CC) -Wall -c ./src/objects/ship.c -o ./build/ship.o
	$(CC) -Wall -c ./src/globals.c -o ./build/globals.o
	$(CC) -Wall -c ./src/rng.c -o ./build/rng.o
	$(CC) -Wall -c ./src/main.c -o ./build/main.o

clean:
	rm -rf ./build
