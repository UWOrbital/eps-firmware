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

# Flash & Build Script

To perform a new clean build of the application and flash the board, run the following command:
```shell
bash new_build.sh -p <project>
```

Example:
```shell
bash new_build.sh -p blinky
```

# Build & Flash Manually

Alternatively, you can build the application manually and flash the board.: 
```shell
rm -rf build
source ~/zephyrproject/zephyr/zephyr-env.sh 
west build -b blackpill_f411ce <project> --pristine
west flash
```

# Flashing the Black Pill

[Reference](https://docs.zephyrproject.org/2.6.0/boards/arm/blackpill_f411ce/doc/index.html)

Connect a USB-C cable and the board should power ON. Force the board into DFU mode by keeping the BOOT0 switch pressed while pressing and releasing the NRST switch.

# Logging

For logging, you will have to use UART1 on the board, in particular UART1 has been tested, the `usb_cdc` project is a good example of this. As a sample, see `usb_cdc`. 

Build and flash the app `usb_cdc`:
```
bash new_build.sh -p usb_cdc
```

Leave the USB C connected to the board and laptop, additionally you will have to connect a TTL to USB adapter (such as [TTL to USB](https://www.amazon.ca/DSD-TECH-Adapter-FT232RL-Compatible/dp/B07BBPX8B8/ref=sr_1_6?crid=2KDPX5YSTAU0Y&keywords=ttl+to+usb+adapter&qid=1655674592&sprefix=ttl+to+usb+adapter%2Caps%2C237&sr=8-6)) to UART1 on the black pill. For this connect TXD on the adapter to A10 on the blackpill, and RXD on the adapter to A9 on the blackpill.

Now open 2 terminals, run the each command in seperate terminals:

Terminal 1:
```shell
minicom -b 115200 --device /dev/ttyUSB0
```

Terminal 2:
```shell
minicom -b 115200 --device /dev/ttyACM0
```

You should see something similar in Terminal 1: 
```
*** Booting Zephyr OS build v3.1.0-rc3-77-ge27565e34da2  ***                    
[00:00:00.006,000] <inf> cdc_acm_echo: Wait for DTR                             
[00:00:00.012,000] <inf> usb_cdc_acm: Device suspended                          
[00:00:00.106,000] <inf> cdc_acm_echo: wait uart_line_ctrl_get()                
[00:00:00.306,000] <inf> cdc_acm_echo: wait uart_line_ctrl_get()                
[00:00:00.456,000] <inf> usb_cdc_acm: Device configured                         
[00:00:00.506,000] <inf> cdc_acm_echo: wait uart_line_ctrl_get()                
[00:00:00.707,000] <inf> cdc_acm_echo: wait uart_line_ctrl_get()                
[00:00:00.907,000] <inf> cdc_acm_echo: wait uart_line_ctrl_get()                
[00:00:01.007,000] <inf> cdc_acm_echo: DTR set                                  
[00:00:02.018,000] <inf> cdc_acm_echo: Baudrate detected: 115200                
[00:00:02.018,000] <inf> cdc_acm_echo: Main loop...                             
```

## Using an overlay file

```shell
west build -b blackpill_f411ce adc --pristine -DDTC_OVERLAY_FILE=boards/stm32l496g_disco.overlay
```
