#!/usr/bin/env bash

TOOLCHAIN_DIR="/mnt/work/wenger00/toolchain"


#BUILD=
#HOST=
TARGET="aarch64-unknown-linux"

CROSS_PREFIX="aarch64-unknown-linux-"

BUILD_DIR="build"
SOURCE_DIR=$(pwd)
DEST_DIR="$TOOLCHAIN_DIR"

#
test -d $BUILD_DIR && rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR

# =========================================================================== #

notice() {
	local
	echo -ne "\e[32m"
	echo -ne "$@"
	echo -ne "\e[0m"
	echo -ne "\n"
}

# =========================================================================== #


#
cd $BUILD_DIR && {
	#
	$SOURCE_DIR/configure --prefix=/usr --target=$TARGET --disable-multib

	#
	make -j4

	#
	make install DESTDIR=$DEST_DIR

	#
	cd - </dev/null
}

