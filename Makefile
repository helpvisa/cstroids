OUTPUT=cstroids
CC=cc
LINK_COMMANDS=-lm -lSDL2
COMPILE_COMMANDS=

main: assemble
	$(CC) -Wall ./build/*.o -o ./$(OUTPUT) $(LINK_COMMANDS)

assemble:
	mkdir -p ./build
	$(CC) -Wall -c ./src/wrap_sdl/draw.c -o ./build/draw.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/wrap_sdl/init.c -o ./build/init.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/wrap_sdl/input.c -o ./build/input.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/generic/collide.c -o ./build/collide.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/objects/particle.c -o ./build/particle.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/objects/asteroid.c -o ./build/asteroid.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/objects/ship.c -o ./build/ship.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/globals.c -o ./build/globals.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/rng.c -o ./build/rng.o $(COMPILE_COMMANDS)
	$(CC) -Wall -c ./src/main.c -o ./build/main.o $(COMPILE_COMMANDS)

clean:
	rm -rf ./build
