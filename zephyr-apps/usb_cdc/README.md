# Usage

After building and flashing the app leave the USB C connected to the board and laptop, additionally you will have to connect a TTL to USB adapter (such as [TTL to USB](https://www.amazon.ca/DSD-TECH-Adapter-FT232RL-Compatible/dp/B07BBPX8B8/ref=sr_1_6?crid=2KDPX5YSTAU0Y&keywords=ttl+to+usb+adapter&qid=1655674592&sprefix=ttl+to+usb+adapter%2Caps%2C237&sr=8-6)) to UART1 on the black pill. For this connect TXD on the adapter to A10 on the blackpill, and RXD on the adapter to A9 on the blackpill.

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