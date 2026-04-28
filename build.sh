#!/bin/bash
set -e

echo "Building WASM..."
mkdir -p build/web

RAYLIB_SRC=/tmp/raylib-src/src

emcc src/main.c \
  -o build/web/index.html \
  --shell-file web/shell.html \
  -I${RAYLIB_SRC} \
  -L${RAYLIB_SRC} -lraylib_web \
  -s USE_GLFW=3 \
  -s TOTAL_MEMORY=33554432 \
  -s FORCE_FILESYSTEM=1 \
  -DPLATFORM_WEB \
  -O2

echo "Build complete -> build/web/"
