# Zephyr Apps

Each application will contain its own directory within this folder. 

# Overview

Each application will have at minimun the following structure:
```
app
├── CMakeLists.txt
├── prj.conf
└── src
    └── main.c
```

**Blackpill Reference:** https://docs.zephyrproject.org/2.6.0/boards/arm/blackpill_f411ce/doc/index.html

# Flash & Build Script

To perform a new clean build of the application and flash the board, run the following command:
```shell
bash new_build.sh -p <project> -b <board> -o <overlay>
```

Example:
```shell
bash new_build.sh -p blinky -b blackpill_f411ce
```

Example with overlay:
```shell
bash new_build.sh -p mppt -b blackpill_f411ce -o overlays/blackpill_f411ce.overlay
```

# Build & Flash Manually

Alternatively, you can build the application manually and flash the board.: 
```shell
rm -rf build
source ~/zephyrproject/zephyr/zephyr-env.sh 
west build -b blackpill_f411ce <project> --pristine
west flash
```

# Overlays
Absolute path of overlay(s) needs to be passed to `west build`. `pwd` command can be used to obtain absolute path to current directory in most unix based terminals.

Example:
```shell
west build -b stm32l476g_disco gpio --pristine -DDTC_OVERLAY_FILE=${PWD}/overlays/stm32l476g_disco.overlay
```

`new_build.sh` inserts absolute path to directory containing the `new_build.sh` before overlay argument.

Example:
```shell
bash new_build.sh -p gpio -b stm32l476g_disco -o overlays/stm32l476g_disco.overlay
```

# Flashing the Black Pill

[Reference](https://docs.zephyrproject.org/2.6.0/boards/arm/blackpill_f411ce/doc/index.html)

Connect a USB-C cable and the board should power ON. Force the board into DFU mode by keeping the BOOT0 switch pressed while pressing and releasing the NRST switch.

# Logging

For logging, you will have to use UART1 on the board, in particular UART1 has been tested, any app can be used as an example, either test using `blinky` or see `mppt`. 

Build and flash the app `mppt`:
```
bash new_build.sh -p mppt -b blackpill_f411ce -o overlays/blackpill_f411ce.overlay
```

Leave the USB C connected to the board and laptop, additionally you will have to connect a TTL to USB adapter (such as [TTL to USB](https://www.amazon.ca/DSD-TECH-Adapter-FT232RL-Compatible/dp/B07BBPX8B8/ref=sr_1_6?crid=2KDPX5YSTAU0Y&keywords=ttl+to+usb+adapter&qid=1655674592&sprefix=ttl+to+usb+adapter%2Caps%2C237&sr=8-6)) to UART1 on the black pill. 

For this connect TXD on the adapter to A10 on the blackpill, and RXD on the adapter to A9 on the blackpill.

Now open a terminal, run the following command in the terminal:
```shell
sudo minicom -D /dev/ttyUSB0
```

You should see something similar: 
```
*** Booting Zephyr OS build zephyr-v3.1.0-1496-g9e3d697f151a  ***
[00:00:00.005,000] <inf> mppt_adc: ADC(ADC_1), channel [1]: Configured
[00:00:00.005,000] <inf> mppt_adc: ADC(ADC_1), channel [4]: Configured
[00:00:00.005,000] <inf> mppt: Running Main()...
[00:00:00.005,000] <inf> mppt_adc: - ADC_1, channel 1: 
[00:00:00.005,000] <inf> mppt_adc: millivolts = 2574 mV
[00:00:00.005,000] <inf> mppt_adc: - ADC_1, channel 4: 
[00:00:00.005,000] <inf> mppt_adc: millivolts = 2575 mV
[00:00:02.505,000] <inf> mppt: Running Main()...
[00:00:02.505,000] <inf> mppt_adc: - ADC_1, channel 1: 
[00:00:02.505,000] <inf> mppt_adc: millivolts = 2567 mV
[00:00:02.505,000] <inf> mppt_adc: - ADC_1, channel 4: 
[00:00:02.506,000] <inf> mppt_adc: millivolts = 2582 mV
[00:00:05.006,000] <inf> mppt: Running Main()...
[00:00:05.006,000] <inf> mppt_adc: - ADC_1, channel 1: 
[00:00:05.006,000] <inf> mppt_adc: millivolts = 2570 mV
[00:00:05.006,000] <inf> mppt_adc: - ADC_1, channel 4: 
[00:00:05.006,000] <inf> mppt_adc: millivolts = 2572 mV
```
