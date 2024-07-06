#!/bin/sh

make CC=x86_64-w64-mingw32-gcc OUTPUT=cstroids.exe LINK_COMMANDS="-mwindows -lmingw32 -lSDL2main -lSDL2"
