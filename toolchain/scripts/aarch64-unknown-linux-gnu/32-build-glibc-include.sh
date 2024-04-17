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
#
PATH="$TOOLCHAIN_PATH/bin${PATH:+:$PATH}"
CC=${CROSS_PREFIX}gcc
export PATH CC

##
test -d $BUILD_PATH && rm -rf $BUILD_PATH
mkdir -p $BUILD_PATH

##
cd $BUILD_PATH && {
###################

#
$SOURCE_PATH/configure --prefix=/ \
	--host=$TARGET \
	--target=$TARGET \
	--disable-multilib \
	--with-headers=$TOOLCHAIN_PATH/include \

#
make install-bootstrap-headers=yes install-headers

#
make -j4 csu/subdir_lib

#
install csu/crt1.o csu/crti.o csu/crtn.o $DEST_PATH/lib

#
${CC} -nostdlib -nostartfiles -shared -x c /dev/null -o $DEST_PATH/lib/libc.so

#
install -d $DEST_PATH/include/gnu/
touch $DEST_PATH/include/gnu/stubs.h

###################
	cd - >/dev/null
}