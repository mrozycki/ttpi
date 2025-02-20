Use `build.sh` to build the target

The output is in `build/src/`

Programming (your interface may vary, e.g. you might use picoprobe)

```
openocd -f interface/cmsis-dap.cfg -c "adapter speed 5000" -f target/rp2040.cfg -c "program build/src/pico_typewriter.elf verify reset exit"
```

Checking logs:

```
probe-rs attach --chip RP2040 --speed 5000 build/src/pico_typewriter.elf
```