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
export PATH

##
test -d $BUILD_RPATH && rm -rf $BUILD_RPATH
mkdir -p $BUILD_RPATH
#
test -d $DEST_APATH && rm -rf $DEST_APATH

##
cd $BUILD_RPATH && {
###################

#
$SOURCE_PATH/configure --prefix=/ \
	--target=$TARGET \
	--enable-languages=c,c++ \
	--disable-multilib \
	--disable-threads \

	--with-sysroot=

	# --with-sysroot=${TOOLCHAIN_DIR} \

	# --disable-shared \
	# --disable-nls \

	# --disable-libssp \
	# --disable-decimal-float \
	# --disable-libatomic \
	# --disable-libquadmath \
	# --disable-libmudflap \
	# --disable-libgomp \



#
make -j4 all-gcc

#
make install-gcc DESTDIR=${DEST_APATH}

###################
	cd - >/dev/null
}