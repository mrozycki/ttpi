Erika Typewriter Hacking Playground
=====

Local development setup
---


### Using nix
#### Setup

1. Install nix by following instructions at https://nixos.org/download
2. Add the following line to /etc/nix/nix.conf:

    experimental-features = nix-command flakes

3. (optional) Install direnv and direnv VSCode extension.

#### Workflow

Use `nix develop` to enter development shell. From there you'll have access to any tools and dependencies needed for development.

### Building and running

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