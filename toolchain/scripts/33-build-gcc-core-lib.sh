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
cd $BUILD_PATH && {
###################

#
make -j4 all-target-libgcc

#
make install-target-libgcc DESTDIR=${DEST_PATH}

###################
	cd - >/dev/null
}


#
#
# 如果出现以下问题：
# 	x86_64-unknown-linux-ld: cannot find crti.o: No such file or directory
# 	x86_64-unknown-linux-ld: cannot find -lc: No such file or directory
# 	x86_64-unknown-linux-ld: cannot find crtn.o: No such file or directory
#
# 请将工具链中 lib/crt1.o, lib/crti.o, lib/crtn.o, lib/libc.so 拷贝到gcc编译目录 build/x86_64-unknown-linux/libgcc 下，再次编译
#
