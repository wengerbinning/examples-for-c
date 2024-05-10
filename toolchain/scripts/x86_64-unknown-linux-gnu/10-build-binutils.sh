#!/usr/bin/env bash

##
TOOLCHAIN_HOME="/mnt/work/toolchains"
TOOLCHAIN_NAME="toolchain-x86_64-unknown-linux-gnu"
TOOLCHAIN_PATH="${TOOLCHAIN_HOME}/${TOOLCHAIN_NAME}"
#
ARCH=x86_64
TARGET="x86_64-unknown-linux-gnu"
CROSS_PREFIX="x86_64-unknown-linux-gnu-"

##
BUILD_PATH=".build"
SRC_APATH=$PWD
DST_APATH=${PWD}/destdir

##
test -d  "$DST_APATH" && rm -rf  "$DST_APATH"
test -d "$BUILD_PATH" && rm -rf "$BUILD_PATH"
mkdir -p $BUILD_PATH

##
cd $BUILD_PATH && {
###################

#
$SRC_APATH/configure --prefix='' \
	--target=$TARGET \
	--with-sysroot=/ \

#
make -j6

#
make install DESTDIR=$DST_APATH

###################
	cd - </dev/null
}
