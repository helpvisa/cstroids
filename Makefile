.POSIX:
.SUFFIXES:
CC = cc
LDLIBS = -lm -lSDL2
LDFLAGS = 
CFLAGS =
OUTPUT = cstroids
PREFIX = /usr/local

OS_FLAG != uname -s

# assumed default OS is Linux
ifeq ($(OS_FLAG),FreeBSD)
	LDLIBS:=-L/usr/local/lib $(LDLIBS)
	CFLAGS:=-I/usr/local/include $(CFLAGS)
endif

all: cstroids
install: cstroids
	cp ./$(OUTPUT) $(PREFIX)/bin
uninstall:
	rm $(PREFIX)/bin/$(OUTPUT)
cstroids: build/draw.o\
	build/init.o\
	build/input.o\
	build/collide.o\
	build/particle.o\
	build/asteroid.o\
	build/bullet.o\
	build/ship.o\
	build/particle-helpers.o\
	build/globals.o\
	build/rng.o\
	build/main.o
	$(CC) -Wall $(LDFLAGS) -o ./$(OUTPUT)\
		build/draw.o\
		build/init.o\
		build/input.o\
		build/collide.o\
		build/particle.o\
		build/asteroid.o\
		build/bullet.o\
		build/ship.o\
		build/particle-helpers.o\
		build/globals.o\
		build/rng.o\
		build/main.o\
		$(LDLIBS)
build/draw.o: mkdir src/wrap_sdl/draw.c src/wrap_sdl/draw.h
	$(CC) -Wall $(CFLAGS) -c src/wrap_sdl/draw.c -o build/draw.o
build/init.o: mkdir src/wrap_sdl/init.c src/wrap_sdl/init.h
	$(CC) -Wall $(CFLAGS) -c src/wrap_sdl/init.c -o build/init.o
build/input.o: mkdir src/wrap_sdl/input.c src/wrap_sdl/input.h
	$(CC) -Wall $(CFLAGS) -c src/wrap_sdl/input.c -o build/input.o
build/collide.o: mkdir src/generic/collide.c src/generic/collide.h
	$(CC) -Wall $(CFLAGS) -c src/generic/collide.c -o build/collide.o
build/particle.o: mkdir src/objects/particle.c src/objects/particle.h
	$(CC) -Wall $(CFLAGS) -c src/objects/particle.c -o build/particle.o
build/asteroid.o: mkdir src/objects/asteroid.c src/objects/asteroid.h
	$(CC) -Wall $(CFLAGS) -c src/objects/asteroid.c -o build/asteroid.o
build/bullet.o: mkdir src/objects/bullet.c src/objects/bullet.h
	$(CC) -Wall $(CFLAGS) -c src/objects/bullet.c -o build/bullet.o
build/ship.o: mkdir src/objects/ship.c src/objects/ship.h
	$(CC) -Wall $(CFLAGS) -c src/objects/ship.c -o build/ship.o
build/particle-helpers.o: mkdir src/helpers/particle-helpers.c src/helpers/particle-helpers.h
	$(CC) -Wall $(CFLAGS) -c src/helpers/particle-helpers.c -o build/particle-helpers.o
build/globals.o: mkdir src/globals.c src/globals.h
	$(CC) -Wall $(CFLAGS) -c src/globals.c -o build/globals.o
build/rng.o: mkdir src/rng.c src/rng.h
	$(CC) -Wall $(CFLAGS) -c src/rng.c -o build/rng.o
build/main.o: mkdir src/main.c
	$(CC) -Wall $(CFLAGS) -c src/main.c -o build/main.o
mkdir:
	mkdir -p ./build
clean:
	rm -rf ./build
	rm ./$(OUTPUT)
os:
	@echo Using $(OS_FLAG) environment.
	@echo LDLIBS: \"$(LDLIBS)\"
	@echo CFLAGS: \"$(CFLAGS)\"
