#!/bin/sh
export LD_LIBRARY_PATH=.

g++ -c main.cpp                    # main.o creating object files
g++ -c aSum.cpp                    # aSum.o
g++ -fPIC -c soSum.cpp             # soSum.o with position independent asm code
ar rc libSum.a aSum.o              # libSum.a creating static library (archive)
g++ -shared -o libSum.so soSum.o   # libSum.so creating dynamic library (shared object)
g++ main.o libSum.a libSum.so -ldl # a.out
./a.out

rm *.a *.o *.so *.out
