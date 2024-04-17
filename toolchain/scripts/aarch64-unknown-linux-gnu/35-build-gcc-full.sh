#!/usr/bin/env bash

TOOLCHAIN_PATH="/mnt/work/toolchains/toolchain-x86_64-unknown-linux"

TARGET="x86_64-unknown-linux"

CROSS_PREFIX="x86_64-unknown-linux-"

BUILD_PATH="build"
SOURCE_PATH=$(pwd)

DEST_PATH=$TOOLCHAIN_PATH

#
PATH="$TOOLCHAIN_PATH/bin${PATH:+:$PATH}"
export PATH

CC=${CROSS_PREFIX}gcc
export CC

#
cd $BUILD_PATH && {
###################

#
make -j4

#
make install DESTDIR=${DEST_PATH}

###################
	cd - >/dev/null
}