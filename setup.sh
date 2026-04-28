#!/bin/bash
set -e

echo "Building raylib for WebAssembly..."

RAYLIB_VERSION=5.5
RAYLIB_SRC=/tmp/raylib-src/src

if [ ! -d "/tmp/raylib-src" ]; then
  git clone --depth 1 --branch ${RAYLIB_VERSION} https://github.com/raysan5/raylib.git /tmp/raylib-src
fi

cd ${RAYLIB_SRC}
emcc -c rcore.c rshapes.c rtextures.c rtext.c rmodels.c utils.c \
  -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 -I. -O2
emar rcs libraylib_web.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o utils.o

echo "Done. You can now run ./build.sh or ./deploy.sh"
