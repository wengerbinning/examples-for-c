#!/usr/bin/env bash

##
ARCH=aarch64
TARGET="aarch64-unknown-linux-gnu"
#
CROSS_PREFIX="aarch64-unknown-linux-gnu-"
CROSS_COMPILE="aaarch64-unknown-linux-gnu-"
#
SOURCE_PATH=$(pwd -P)
DEST_APATH="$SOURCE_PATH/destdir"
#
INSTALL_HDR_PATH=$DEST_APATH


##
case $ARCH in
aarch64)
    ARCH="arm64";;
esac

##
make ARCH=$ARCH headers_install INSTALL_HDR_PATH=$INSTALL_HDR_PATH