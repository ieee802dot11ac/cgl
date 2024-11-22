#!/usr/bin/sh

rm -r obj/* bin/*
mkdir -p obj
mkdir -p bin
for file in $(find src -name "*.c"); do
		gcc -g -c -o $(printf "obj/%s.o" $(basename $file .c)) $file
done

gcc -lGL -lm -lSDL2 -o bin/cgl obj/*.o
