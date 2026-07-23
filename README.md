# Mica Keyboard
A fully custom keyboard, inspired by Christian Selig's [Caldera](https://christianselig.com/2024/07/caldera-keyboard/) and FlatFootFox's [Ergogen tutorial](https://flatfootfox.com/ergogen-introduction/).

The Mica keyboard is
- **modular** via a 3.3V I2C bus connected to ports on the left, right, and top of the case,
- **split and ortholinear** to facilitate long typing sessions,
- **fully wireless** with BLE connections between the keyboard halves and the host, and
- **portable** via a thin design with Choc switches.

## Instructions

If you would like to build this keyboard:

1. get the design files from the [Releases](https://github.com/ilauzon/mica-keyboard/releases) section ([or make them yourself](docs/software-build-instructions.md)):
    - Gerber files to send to a PCB manufacturer
    - 3D models of the case to print
    - Firmware to flash onto your microcontroller (a nice!nano V2)
2.  Read the [build instructions](docs/build-instructions.md) to put it all together.
