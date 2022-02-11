# MPPT Sample Application

A sample application that demonstrates the use of the MPPT algorithm - to be converted to a final build when the time arises.

## Application functionality

The `main()` function toggles the state of a digital output connected to an LED on the board and prints to the terminal.

## Expected output 

The LED on your target turns on and off every 500 milliseconds, and the serial terminal shows an output similar to: 

```
--- Terminal on /dev/tty.usbmodem21102 - 9600,8,N,1 ---
Running on Mbed OS 6
``` 

## Configuring the application

The current application uses the full mbed-os library. However, to decrease size and perform optimizations, we can configure the application to use only use specific profiles and configurations.

### The bare metal profile

The bare metal profile is a configuration of Mbed OS that excludes the RTOS, as well as other features. We designed it specifically for ultraconstrained devices because it gives you more control over the system. For more details, please see [the bare metal documentation](https://os.mbed.com/docs/mbed-os/latest/reference/mbed-os-bare-metal.html)

To build with the bare metal profile, the application configuration file must contain:

```json
{
    "requires": ["bare-metal"]
}
```

### Futher optimizations
Some of the configurations shown below are already set by default in `targets/targets.json` and `platform/mbed_lib.json`.
#### Linking with smaller C libraries

Both the `ARM` and `GCC_ARM` toolchains support optimized versions of their C standard libraries, microlib and newlib-nano. We recommend using them with the bare metal profile.

To build with the smaller C libraries, modify the application configuration file:

```json
{
    "target_overrides": {
        "*": {
            "target.c_lib": "small"
        }
    }
}
```

The build system reverts to the standard C library if support for the small C library is not enabled for your target. You can find more information [here]( https://github.com/ARMmbed/mbed-os-5-docs/blob/development/docs/program-setup/bare_metal/c_small_libs.md).

#### Using Mbed minimal printf library

Mbed OS offers a smaller `printf()` alternative. The [minimal printf](https://github.com/ARMmbed/mbed-os/blob/master/platform/source/minimal-printf/README.md) library implements a subset of the `v/s/f/printf` function family, and you can disable floating points to further reduce code size.

To build with the minimal printf library and disable floating points printing, you need to modify the application configuration file:

```json
{
    "target_overrides": {
        "*": {
            "target.printf_lib": "minimal-printf",
            "platform.minimal-printf-enable-floating-point": false
        }
    }
}
```

Further optimizations are possible. For more details, please see the minimal printf README.

#### Using a minimal console

If your application only needs unbuffered I/O operations, you can save additional memory by using a configuration of the platform library, which removes file handling functionality from the [system I/O retarget code](https://github.com/ARMmbed/mbed-os/blob/master/platform/source/mbed_retarget.cpp).

To build with the minimal console functionality, modify the application configuration file:

```json
{
    "target_overrides": {
        "*": {
            "platform.stdio-minimal-console-only": true
        }
    }
}
```

#### Memory comparison

The below table shows the result for the blinky bare metal application compiled with the release profile on K64F for the GCC_ARM toolchain.

The baseline configuration used is the blinky bare metal application built with the standard C library.

Mbed OS release: mbed-os-6.0.0-alpha-2

|Standard C lib|Small C lib|Minimal printf|Minimal console|RAM|Flash|
| :---:        | :---:     | :---:        | :---:         | :---: | :---: |
| X            |           |              |               | 0 | 0 |
|              | X         |              |               | -2,592 | -28,581 |
|              | X         | X            |               | -2,592 | -29,918 |
|              | X         | X            | X             | -2,592 | -30,810 |

## Troubleshooting 

If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it. 

## Related links 

- [Mbed OS bare metal](https://os.mbed.com/docs/mbed-os/latest/reference/mbed-os-bare-metal.html).
- [Mbed OS configuration](https://os.mbed.com/docs/latest/reference/configuration.html). 
- [Mbed OS serial communication](https://os.mbed.com/docs/latest/tutorials/serial-communication.html). 
- [Mbed boards](https://os.mbed.com/platforms/).
