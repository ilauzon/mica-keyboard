# Mica Keyboard
The **Mica** keyboard is a modular, split, and wireless keyboard.

The Mica keyboard has the following features:
- Support for hotswappable I2C modules on the left, right, and top of the case
- Choc keyswitches for a compact design
- Bluetooth for a fully wireless experience
- Stable and adjustable tenting solution
- A lightweight case that keeps dust out without compromising durability
- Status indicator lights for layer indication and troubleshooting

Creation of this keyboard was inspired by Christian Selig's [Caldera](https://christianselig.com/2024/07/caldera-keyboard/). I also followed FlatFootFox's [Ergogen tutorial](https://flatfootfox.com/ergogen-introduction/) in the making of this keyboard.

## Instructions

If you would like to build this keyboard for yourself, see the Releases section of this GitHub repository for the following:
- Gerber files to send to a PCB manufacturer
- 3D models of the case to print
- Firmware to flash onto your MCU (A nice!nano v2)

If you want to build this or a similar keyboard from source, keep reading!

### Prerequisites

- POSIX-compliant environment (macOS, Linux, Git Bash for Windows)
- npm (to install Ergogen)
- podman (to build the firmware)
- make (to build the firmware)

### (TODO) Bill of Materials
### (TODO) Step 1: Using Ergogen to generate the base PCB and 3D models

To generate the files needed to build the keyboard (PCB, case design):
1. Install ergogen.
```shell
npm i ergogen
```
2. Build the PCB and case.
```shell
npm run build
npm run case
```

### (TODO) Step 2: Editing the PCB with KiCad
### Step 3: Building and flashing the firmware

To build the firmware, simply run `cd firmware && make`. This will create two files in `firmware/build`: `zmk_left.uf2` and `zmk_right.uf2`. Flash each half of your keyboard accordingly. The Makefile pulls down the ZMK source tree and build tools to build the firmware, so the first build will be absolutely glacial. Subsequent builds should be reasonably fast.

I opted to configure my project to build the firmware locally instead of ZMK's recommended approach of using GitHub Actions. I wanted to be able to test out features quickly without commiting and pushing every test. I followed ZMK's [Podman guide](https://zmk.dev/docs/development/local-toolchain/setup/container) to accomplish this.
