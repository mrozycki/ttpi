#!/bin/sh

set -e

cmake -B build -G Ninja

if [ "$1" == "flash" ]; then
    ninja -C build
    openocd -f interface/cmsis-dap.cfg -c "adapter speed 5000" -f target/rp2040.cfg -c "program build/src/pico_typewriter.elf verify reset exit"
    probe-rs attach --chip RP2040 --speed 5000 build/src/pico_typewriter.elf
else
    ninja -C build $1
fi;

