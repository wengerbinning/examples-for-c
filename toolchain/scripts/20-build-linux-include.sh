#!/usr/bin/env bash

TOOLCHAIN_DIR="/mnt/work/wenger00/toolchain"

TARGET="aarch64-unknown-linux"
CROSS_PREFIX="aarch64-unknown-linux-"
ARCH=arm64

SOURCE_DIR=$(pwd)
DEST_DIR="$TOOLCHAIN_DIR"


INSTALL_HDR_PATH=$TOOLCHAIN_DIR

# =========================================================================== #

notice() {
    local
    echo -ne "\e[32m"
    echo -ne "$@"
    echo -ne "\e[0m"
    echo -ne "\n"
}

# =========================================================================== #

make ARCH=$ARCH headers_install INSTALL_HDR_PATH=$INSTALL_HDR_PATH