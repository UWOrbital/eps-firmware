#!/bin/bash

# Remove the build folder if it exists
rm -rf build

# Config $ZEPHYR_BASE
# This is the base path of the Zephyr project installation
source ~/zephyrproject/zephyr/zephyr-env.sh 

# Build app for blackpill
west build -b stm32l476g_disco gpio -- -DDTC_OVERLAY_FILE="~/orbital/eps/eps-firmware/zephyr-apps/overlays/custom-pin.overlay"
west flash