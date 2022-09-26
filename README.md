# EPS firmware

A repository for all EPS related firmware. 

There are currently two main embedded frameworks/sdks supported, primarily [Zephyr](https://docs.zephyrproject.org/latest/introduction/index.html) however in the past [Mbed](https://os.mbed.com/mbed-os/) was used.

Current development uses the Zephyr RTOS.

# Zephyr RTOS Setup

For developing using Zephyr it is recommended you use either OSX or Linux (Ubuntu in particular) as your OS. If you are using Windows it is recommended you dual boot your system to run both Ubuntu and Windows.

## Windows / Ubuntu Dual Boot

If you choose to develop on linux, here is a guide to dual boot your system to run both windows and ubuntu: [Windows/Ubuntu Dual Boot](https://itsfoss.com/install-ubuntu-1404-dual-boot-mode-windows-8-81-uefi/)

## Ubuntu Install

Follow the guide [here](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to setup Zephyr RTOS, ensure you are following the Ubuntu instructions selected.

Once you reach the section *Get Zephyr and install Python dependencies*, it is recommended you try and install within a virtual environment. 

**Note**: If you run into issues with installing within a virtual environment, try installing globally. 

After either installing within a virtual environment or globally, resume following the Zephyr Getting Started Guide from the *Install Zephyr SDK* section.  

Notes: 
- It is recommneded you install the Zephyr base at the root of your user (`~/zephyrproject`)

See the [Beyond Getting Started Guide](https://docs.zephyrproject.org/3.0.0/guides/beyond-GSG.html) for more information on the setup process. 

## OSX Install 

Follow the guide [here](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to setup Zephyr RTOS, ensure you are following the macOS instructions selected.

Once you reach the section *Get Zephyr and install Python dependencies*, it is recommended you try and install within a virtual environment. 

**Note**: If you run into issues with installing within a virtual environment, try installing globally. 

After either installing within a virtual environment or globally, resume following the Zephyr Getting Started Guide from the *Install Zephyr SDK* section.  

Notes: 
- It is recommneded you install the Zephyr base at the root of your user (`~/zephyrproject`)

See the [Beyond Getting Started Guide](https://docs.zephyrproject.org/3.0.0/guides/beyond-GSG.html) for more information on the setup process. 

### Common Errors and Notes

While running some of the steps you may encounter some errors, below are some different steps to try instead: 

[1] When running the pip install, add the --user flag 
```
pip3 install -r ~/zephyrproject/zephyr/scripts/requirements.txt --user
```

[2] When trying to build a application you may get the following error: 
```
FileNotFoundError: [Errno 2] No such file or directory: 'dfu-util'
```

Try installing `dfu-util` using homebrew: 
```
brew install dfu-util
```

[3] When trying to brew install packages you may get an error as follows: 
```
Linking /usr/local/Cellar/libmagic/5.43... 
Error: Could not symlink share/misc/magic.mgc
Target /usr/local/share/misc/magic.mgc
```

Try running the following: 
```
sudo chown -R `whoami`:admin /usr/local/share
brew link --overwrite libmagic
```

Additional steps if that does not work can be found here: [Homebrew: Could not symlink](https://stackoverflow.com/questions/26647412/homebrew-could-not-symlink-usr-local-bin-is-not-writable)


# Additional Install Instructions

## Using Minicom

On linux/OSX you can utilize minicom for logging output, to setup: 

```
sudo apt install minicom -y
```

To view availible devices:
```
ls /dev
```

Often you'll find a device under `/dev/ttyUSB0` or possibly `/dev/ttyACM0` for example, then you can connect and log the serial output with: 
```
sudo minicom -D /dev/ttyUSB0
```

**Note:** If you are using **Ubuntu 22.04** you may be unable to see the USB device `/dev/ttyUSB0` which is the device of the serial to USB converter.
In order to solve this, run the following command: 
```
sudo apt remove brltty
```

## Setting Up SSH Keys

When cloning the repository, clone using `ssh`. If you get a *permission denied* when cloning using SSH or when trying to push to the repository after being added, you may need to setup and add your SSH keys for your local machine, follow the guide below: 

[Generate SSH Keys](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)

## Installing a 3rd Party Toolchain

(**Note:** This is not required, only for reference)

[Reference](https://docs.zephyrproject.org/3.0.0/getting_started/toolchain_3rd_party_x_compilers.html)

Going to use the GNU arm embedded toolchain since it supports ARM based SoCs.
Install [gcc-arm-none-eabi-10-2020-q4-major](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads/product-release) from the GNU website. 

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

## Virtual Environments

### Create Virtual Enviroment (macOS)

Create: 
```
python3 -m venv ~/zephyrproject/.venv
```

Activate: 
```
source ~/zephyrproject/.venv/bin/activate
```

### Create Virtual Enviroment (Ubuntu)

Install virtualenv:
```
sudo apt install python3-venv
```

Create:
```
python3 -m venv ~/zephyrproject/.venv
```

Activate:
```
source ~/zephyrproject/.venv/bin/activate
```

# Mbed OS Setup

(**Note:** This is not required, only for reference)

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
