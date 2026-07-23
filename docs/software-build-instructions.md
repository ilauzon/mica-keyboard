# Building the keyboard from scratch

This document describes how to create the build artifacts of this repository, namely the PCB design, 3D models for the case, and firmware to flash your microcontroller.

If you simply want to build the keyboard for yourself without messing around with software, refer to the [build instructions](build-instructions.md) section instead.

## Prerequisites

- POSIX-compliant environment
- npm (for step 1, generating the base PCB and 3D models for the case)
- KiCad (for step 2, to edit the PCB)
- podman, GNU make (for step 3, to build the firmware)

## Instructions

### 1. Generate the base PCB and 3D models

The PCB and case are generated using [Ergogen](https://github.com/ergogen/ergogen/tree/master). I recommend reading FlatFootFox's [tutorial](https://flatfootfox.com/ergogen-introduction/) on the tool if you would like to make modifications.

All you need to do to build the PCB and case is
1. install ergogen,
```shell
npm i ergogen
```
2. then run the build commands.
```shell
npm run build # build the PCB
npm run case # build the case
```

### 2. Edit the PCB

Ergogen does not generate a PCB that is ready right away to manufacture. There are a few things you need to add to it (due not only to limitations of Ergogen, but also limitations of my personal ability to use Ergogen), namely:
- Routing traces for all the components on the board
- Adding the I2C ports on the sides
- Adding the LEDs and SMD resistors
- Adding 3D models for all the parts (optional)

### 3. Build the firmware

```sh
cd firmware
make
```

This will build three `uf2` files in `firmware/build`: `zmk_left.uf2`, `zmk_right.uf2`, and `settings_reset.uf2`. Flash each half of your keyboard accordingly.

The Makefile pulls down the ZMK source tree and build tools to build the firmware, so the first build will be absolutely glacial. Subsequent builds should be reasonably fast.

I opted to configure my project to build the firmware locally instead of ZMK's recommended approach of using GitHub Actions. I wanted to be able to test out features quickly without commiting and pushing every test. I followed ZMK's [Podman guide](https://v0-3-branch.zmk.dev/docs/development/local-toolchain/setup/container?container=podman) - refer to this if you want to change the build options.