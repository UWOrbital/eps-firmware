#!/bin/bash

usage() {
    echo "usage: -p <project>"
}

no_args="true"
while getopts :p: flag; do
    case "${flag}" in
    p)
        project=${OPTARG}
        no_args="false"

        # Remove the build folder if it exists
        rm -rf build

        # Config $ZEPHYR_BASE
        # This is the base path of the Zephyr project installation
        source ~/zephyrproject/zephyr/zephyr-env.sh 

        # Build app for blackpill
        west build -b blackpill_f411ce $project --pristine

        # Flash application to board
        west flash

        ;;
    ?)
        echo "Please pass in an zephyr app to build"
        exit 1
        ;;
    esac
done

[[ "$no_args" == "true" ]] && {
    usage
    exit 1
}
