# cstroids
## tiny asteroids clone written in C using SDL2

Created as an exercise in learning C and SDL.

## Compiling
### Linux
If you're using any Linux distro, all you should need is a C compiler and SDL2's development packages:
``` sh
make
sudo make install
```
Static Linux binaries can be compiled using:
``` sh
make STATIC=1
```
Currently, static binaries can only be compiled on Linux (maybe FreeBSD will work too; it isn't something I've personally tested).

### FreeBSD
If you're on FreeBSD, GNU Make is also required. Install it along with SDL2 and use the following command:
``` sh
gmake FREEBSD=1
sudo make install
```
Compilation has not been tested on any of the other BSDs. Maybe you can try it and let me know?

### Windows (cross-compiling)
You can also cross-compile a Windows binary using mingw32-gcc. Bear in mind you'll need a copy of SDL2.dll (not included here) to run the Windows binary:
``` sh
make WINDOWS_CROSSCOMPILE=1
```
Ironically, Windows binaries can only be easily built on Linux at the moment, but that may change if I decide I'm ready to *really* dig into some Makefile shenanigans.

### MacOS
If you'd like to experiment with compiling on MacOS, I'm sure it's possible but I don't own any Apple products to try that with! Of course, donations for the sake of 'easing development' are appreciated...


## Misc
This project is in active (but slow, hobbyist) development, so no releases yet... but maybe soon :)
