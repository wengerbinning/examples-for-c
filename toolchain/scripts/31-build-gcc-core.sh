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

#
test -d $BUILD_PATH && rm -rf $BUILD_PATH
mkdir -p $BUILD_PATH


cd $BUILD_PATH && {
###################

#
$SOURCE_PATH/configure --prefix=/ \
	--target=$TARGET \
	--enable-languages=c,c++ \
	--disable-multilib \
	--disable-threads \

	# --disable-decimal-float \
	# --disable-shared \
	# --disable-nls \
	# --disable-libatomic \
	# --disable-libquadmath \
	# --disable-libmudflap \
	# --disable-libgomp \
	# --disable-libssp \

	# --with-sysroot=${TOOLCHAIN_DIR} \

#
make -j4 all-gcc

#
make install-gcc DESTDIR=${DEST_PATH}

###################
	cd - >/dev/null
}