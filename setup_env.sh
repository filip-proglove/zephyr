#!/bin/bash

# Scipt for setting up build environment for zephyr v2.3.0

# Before running this script make sure you have installed all the required
# software tools such as:
# - https://docs.zephyrproject.org/2.3.0/getting_started/index.html
# - west
# - zephyr-sdk-0.11.3 (install in the path /opt/zephyr-sdk-0.11.3)
# - nrfjprog 10.9.0
# - Segger JLink v6.80a

name=$(basename -- "$0")
if [ "X$name" "==" "Xsetup_env.sh" ]; then
    echo "Source this file (do NOT execute it!) to set the Zephyr 2.3.0 Kernel environment."
    exit
fi

# Zephyr environment variables setup
export ZEPHYR_BASE=${PWD}
export ZEPHYR_GCC_VARIANT=zephyr
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr

# Zephyr 2.3.0 uses zephyr-sdk version 0.11.3
export ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk-0.11.3
