#!/usr/bin/env bash

##
TOOLCHAIN_HOME="/mnt/work/toolchains"
TOOLCHAIN_NAME="toolchain-x86_64-unknown-linux-gnu"
TOOLCHAIN_PATH="${TOOLCHAIN_HOME}/${TOOLCHAIN_NAME}"
#
ARCH=x86_64
TARGET="x86_64-unknown-linux-gnu"
#
CROSS_PREFIX="x86_64-unknown-linux-gnu-"
#
BUILD_RPATH="build"
SOURCE_PATH=$(pwd -P)
DEST_APATH="$SOURCE_PATH/destdir"
#
INSTALL_HDR_PATH=$DEST_APATH

##
test -d $DEST_APATH && rm -rf $DEST_APATH

##
make ARCH=$ARCH headers_install INSTALL_HDR_PATH=$INSTALL_HDR_PATH