# EPS firmware

A repository for all EPS related firmware. 

# Setup

For the firmware, we are going to use mbed-os to provide drivers and APIs for a varierty of functions. 
To get started I would recommend installing Mbed Studio - however the online compiler and CLI are also viable options. 
This is primarily used to build the application for the target board, other ideas can be used. 

Install Mbed Studio: https://os.mbed.com/studio/
Mbed-os: https://github.com/ARMmbed/mbed-os

Once installed, I would recommend opening this folder in Mbed Studio, then right-click on `mppt-sample-app` and click **Add Library**. 
In the URL field enter: git@github.com:ARMmbed/mbed-os.git and click Next
Select `latest` as the branch to use. 

This should import mbed-os into the directory. Alternatively, you can point to an existing mbed-os instance. 
More information on different setup can be found here: https://os.mbed.com/docs/mbed-studio/current/create-import/index.html

Once you see a `.mbed` file and `mbed-os` folder in the directory you know mbed is imported. 
In mbed studio select a target board to build and build profile as debug. Plug in your board and know you 
should be able to build and flash (Note: When your board is connected there is a green USB icon and output terminal). 