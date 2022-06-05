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

# Build 

To perform a new clean build of the application, run the following command:
```shell
bash new_build.sh
```

# Flash 

Once you have built the application, you can flash it to the target board: 
```shell
west flash
```

# Flashing the Black Pill

[Reference](https://docs.zephyrproject.org/2.6.0/boards/arm/blackpill_f411ce/doc/index.html)

Connect a USB-C cable and the board should power ON. Force the board into DFU mode by keeping the BOOT0 switch pressed while pressing and releasing the NRST switch.

# Using an overlay file

```shell
west build -b blackpill_f411ce adc --pristine -DDTC_OVERLAY_FILE=boards/stm32l496g_disco.overlay
```
