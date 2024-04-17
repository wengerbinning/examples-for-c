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
export PATH

##
test -d $BUILD_RPATH && rm -rf $BUILD_RPATH
mkdir -p $BUILD_RPATH

##
cd $BUILD_RPATH && {
###################

#
$SOURCE_PATH/configure --prefix=/ \
	--target=$TARGET \
	--enable-languages=c,c++ \
	--disable-multilib \
	--disable-threads \

	# --disable-shared \
	# --disable-nls \

	# --disable-libssp \
	# --disable-decimal-float \
	# --disable-libatomic \
	# --disable-libquadmath \
	# --disable-libmudflap \
	# --disable-libgomp \

	# --with-sysroot=${TOOLCHAIN_DIR} \

#
make -j4 all-gcc

#
make install-gcc DESTDIR=${DEST_APATH}

###################
	cd - >/dev/null
}