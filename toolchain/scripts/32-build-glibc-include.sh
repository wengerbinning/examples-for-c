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
test -d $BUILD_PATH && rm -rf $BUILD_PATH
mkdir -p $BUILD_PATH

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