#!/usr/bin/env bash

##
TOOLCHAIN_HOME="/mnt/work/toolchains"
TOOLCHAIN_NAME="x86_64-unknown-linux-gnu"
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

##
test -d $BUILD_RPATH && rm -rf $BUILD_RPATH
mkdir -p $BUILD_RPATH
#
test -d $DEST_APATH && rm -rf $DEST_APATH

##
cd $BUILD_RPATH && {
###################

#
$SOURCE_PATH/configure --target=$TARGET --prefix=/
	--disable-multib

#
make -j4

#
make install DESTDIR=$DEST_APATH

###################
	cd - </dev/null
}
