#!/bin/bash

usage() {
    echo "usage: -p <project> -b <board> -o <overlay>"
}

project=""
board=""
with_overlay="false"
while getopts "p:b:o:" flag; do
    case "${flag}" in
        p)
            project=${OPTARG}
            ;;
        b)
            board=${OPTARG}
            ;;
        o)
            overlay=${OPTARG}
            with_overlay="true"
            ;;
        ?)
            echo "Invalid argument"
            exit 1
            ;;
    esac
done

[[ "$project" == "" || "$board" == "" ]] && {
    usage
    exit 1
}

build_args="-b $board $project --pristine "

[[ $with_overlay = "true" ]] && {
    build_args+="-DDTC_OVERLAY_FILE=${PWD}/$overlay"
}

# source Zephyr project installation
source ~/zephyrproject/zephyr/zephyr-env.sh

echo "New Build: $build_args"

# Remove the build folder if it exists
rm -rf build

# build app
west build $build_args

# flash app to board
west flash
