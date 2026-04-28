#!/bin/bash
set -e

mkdir -p build

gcc src/main.c -o build/game \
  -I/usr/local/include \
  -L/usr/local/lib \
  -lraylib \
  -framework OpenGL \
  -framework Cocoa \
  -framework IOKit

./build/game
