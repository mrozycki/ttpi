#!/bin/sh

cmake -B build -G Ninja && \
ninja -C build $1
exit $?