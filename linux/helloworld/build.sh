#!/bin/bash

DEFAULT_KERNEL_PATH="/lib/modules/6.7.2-arch1-1/kernel/"
DEFAULT_MOD_PATH=$(pwd)

# ARCH=
# CROSS_COMPILE=

KERNEL_PATH="/mnt/work/linux/stable-linux"


make \
    ${ARCH:+ARCH=$ARCH} ${CROSS_COMPILE:+CROSS_COMPILE=$CROSS_COMPILE} \
    -C ${KERNEL_PATH:-$DEFAULT_KERNEL_PATH} \
    M=${MOD_PATH:-$DEFAULT_MOD_PATH} modules



