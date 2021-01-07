# Building

## Goal

Build-system agnostic.  Specifically, the driver program might use one of..

- make
- CMake
- Gyp (generate your projects - node js)
- configure/autoconf/automake

## Approach

sqlite-style single .c and .h file
avoid dependencies/#ifdef mazes
Use POSIX headers/definitions

Ship our own polyfills

## Cautions

Do NOT leverage the `libuv` config, as that is a dependency we wish to avoid.


