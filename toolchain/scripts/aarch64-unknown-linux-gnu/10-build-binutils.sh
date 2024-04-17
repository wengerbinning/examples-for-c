#!/usr/bin/env bash

##
TOOLCHAIN_HOME="/mnt/work/toolchains"
TOOLCHAIN_NAME="toolchain-aarch64-unknown-linux-gnu"
TOOLCHAIN_PATH="${TOOLCHAIN_HOME}/${TOOLCHAIN_NAME}"
#
ARCH=aarch64
TARGET="aarch64-unknown-linux-gnu"
#
CROSS_PREFIX="aarch64-unknown-linux-gnu-"
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
command () {
	${@:-true}; ret=$?;
	test $ret -eq 0 && { echo } || { exit }
}
##
cd $BUILD_RPATH && {
###################

#
$SOURCE_PATH/configure --target=$TARGET --prefix=/
	--disable-multib

#
command \
make -j4

#
make install DESTDIR=$DEST_APATH

###################
	cd - </dev/null
}

