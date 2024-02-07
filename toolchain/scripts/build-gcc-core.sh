#!/usr/bin/env bash

TOOLCHAIN_DIR="/mnt/work/wenger00/toolchain"

TARGET="aarch64-unknown-linux"
CROSS_PREFIX="aarch64-unknown-linux-"

BUILD_DIR="build"
SOURCE_DIR=$(pwd)
DEST_DIR="$TOOLCHAIN_DIR"

#
OLD_PATH=$PATH
PATH="$TOOLCHAIN_DIR/bin${PATH:+:$PATH}"
export PATH

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
	$SOURCE_DIR/configure --prefix=/ \
		--target=$TARGET \
		--enable-languages=c \
		--disable-multilib \
		--disable-threads \
		--disable-decimal-float \
		--disable-shared \
		--disable-nls \
		--disable-libmudflap \
		--disable-libssp \

		# --with-sysroot=${TOOLCHAIN_DIR} \

	#
	make -j4 all-gcc

	#
	make install-gcc DESTDIR=${DEST_DIR}

	#
	make -j4 all-target-gcc

	#
	make install-target-gcc DESTDIR=${DEST_DIR}

    #
    cd - >/dev/null
}
