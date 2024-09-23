# cstroids
## tiny asteroids clone written in C using SDL2

Created as an exercise in learning C and SDL.

## Compiling
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

If you're on FreeBSD, installing the above packages will still be a necessity, but the command changes:
``` sh
make FREEBSD=1
sudo make install
```

You can also cross-compile a Windows binary using mingw32. Bear in mind you'll need a copy of SDL2.dll (not included here) to run the Windows binary:
``` sh
make WINDOWS_CROSSCOMPILE=1
```

If you'd like to experiment with compiling on MacOS, I'm sure it's possible but I don't own any Apple products to try that with! Of course, donations for the sake of 'easing development' are appreciated...

## Misc
This project is in active (but slow, hobbyist) development, so no releases yet... but maybe soon :)
