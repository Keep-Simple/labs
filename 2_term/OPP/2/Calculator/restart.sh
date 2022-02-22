#!/bin/sh

killall Calculator

make distclean
qmake Calculator.pro
compiledb make -j10

open build/Calculator.app
