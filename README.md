# EPS firmware

A repository for all EPS related firmware. 

There are currently two main embedded frameworks/sdks supported, primarily [Zephyr](https://docs.zephyrproject.org/2.6.0/introduction/index.html) however in the past [Mbed](https://os.mbed.com/mbed-os/) was used.

# Zephyr RTOS Setup

Follow the guide [here](https://docs.zephyrproject.org/2.6.0/getting_started/index.html) to setup Zephyr RTOS, **see section beloow on installing a toolchain** when you get to that step. 

See instructions below on installing the python dependencies in a virtual environment, otherwise follow the setup oultined in the [Getting Started Guide](https://docs.zephyrproject.org/2.6.0/getting_started/index.html).

Notes: 
- It is recommended you use either OSX or Linux (Ubunutu is recommended) for development
- It is recommneded you install the Zephyr base at the root of your user (`~/zephyrproject`)

## Installing a 3rd Party Toolchain

Reference: https://docs.zephyrproject.org/latest/getting_started/toolchain_3rd_party_x_compilers.html#gnu-arm-embedded

Going to use the GNU arm embedded toolchain since it supports ARM based SoCs.
Install gcc-arm-none-eabi-10-2020-q4-major from the GNU website. 
Extract and copy the files: 
```
tar -xf gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2
mkdir ~/toolchains
cp -r gcc-arm-none-eabi-10-2020-q4-major ~toolchains 
```

Once you have the toolchain, you can add it to your PATH, by setting the following enviroment variables.

Add to `~/.zshrc` or `~/.bashrc`:
```
export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
export GNUARMEMB_TOOLCHAIN_PATH=~/toolchains/gcc-arm-none-eabi-10-2020-q4-major/
```

## Using a Virtual Environment

Alternatively, you can use a virtual environment to isolate your dependencies. 

Run the following command to create a virtual environment:

Note: `$ZEPHYR_BASE` refers to the absolute path to the Zephyr base installation.
```shell
cd zephyr-apps
python -m venv venv
pip install -r $ZEPHYR_BASE/scripts/requirements.txt
```

Activiate the virtual environment:
```shell
cd zephyr-apps
source venv/bin/activate
```

# Mbed OS Setup

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

# VsCode Configuration

To include custom libraries such as the zephyr rtos base, add the path to the `includePath` in the `.vscode/c_cpp_properties.json` file [link](https://code.visualstudio.com/docs/cpp/config-msvc#_cc-configurations).
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**", "~/zephyrproject/zephyr/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "gnu17",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```
