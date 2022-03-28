#!/bin/sh

name="SystemDialogs"
killall $name

make distclean
qmake "$name.pro"
compiledb make -j10

open "build/$name.app"
