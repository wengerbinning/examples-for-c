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
PATH="$TOOLCHAIN_PATH/bin${PATH:+:$PATH}"
CC=${CROSS_PREFIX}gcc
#CFLAGS="-O3 -g -Wno-attributes"
export PATH CC

##
test -d $BUILD_PATH && rm -rf $BUILD_PATH
mkdir -p $BUILD_PATH
#
test -d $DEST_APATH && rm -rf $DEST_APATH

cd $BUILD_PATH && {
###################

#
$SOURCE_PATH/configure --prefix=/ \
	--host=$TARGET \
	--target=$TARGET \
	--disable-multilib \
	--with-headers=$TOOLCHAIN_PATH/include \

#
make install-bootstrap-headers=yes install-headers DESTDIR=$DEST_APATH

#
make -j4 csu/subdir_lib

#
install -d $DEST_APATH/lib
install -t $DEST_APATH/lib csu/crt1.o csu/crti.o csu/crtn.o

#
${CC} -nostdlib -nostartfiles -shared -x c /dev/null -o $DEST_APATH/lib/libc.so

#
install -d $DEST_APATH/include/gnu/
touch $DEST_APATH/include/gnu/stubs.h

###################
	cd - >/dev/null
}