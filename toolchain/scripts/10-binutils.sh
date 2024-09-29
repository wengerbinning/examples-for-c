#!/usr/bin/env bash

##
error() { echo -en "\e[31m"; echo $@; echo -en "\e[0m"; }
warning() { echo -en "\e[33m"; echo $@; echo -en "\e[0m"; }
notice() { echo -en "\e[32m"; echo $@; echo -en "\e[0m"; }
note() { echo -en "\e[34m"; echo $@; echo -en "\e[0m"; }
debug() { echo -en "\e[32m"; echo $@; echo -en "\e[0m"; }
run_cmd() {
    eval "time $@"
    test $? -ne 0 && { error "running command error!";
        debug "command:$@"
        exit 1
    }
}

##
TOOLCHAIN_HOME="/opt/toolchains"
BUILD_PATH=".build"
#
# ARCH=x86
# TARGET="x86-unknown-linux-gnu"
# CROSS_PREFIX="x86-unknown-linux-gnu-"
# TOOLCHAIN_NAME="toolchain-x86-unknown-linux-gnu"
#
# ARCH=x86_64
# TARGET="x86_64-unknown-linux-gnu"
# CROSS_PREFIX="x86_64-unknown-linux-gnu-"
# TOOLCHAIN_NAME="toolchain-x86_64-unknown-linux-gnu"
#
# ARCH=arm
# TARGET="arm-unknown-linux-gnu"
# CROSS_PREFIX="arm-unknown-linux-gnu-"
# TOOLCHAIN_NAME="toolchain-arm-unknown-linux-gnu"
#
# ARCH=arm64
# TARGET="arm64-unknown-linux-gnu"
# CROSS_PREFIX="arm64-unknown-linux-gnu-"
# TOOLCHAIN_NAME="toolchain-arm64-unknown-linux-gnu"
#
# ARCH=mips
# TARGET="mips-unknown-linux-gnu"
# CROSS_PREFIX="mips-unknown-linux-gnu-"
# TOOLCHAIN_NAME="toolchain-mips-unknown-linux-gnu"
#
# ARCH=mips64
# TARGET="mips64-unknown-linux-gnu"
# CROSS_PREFIX="mips64-unknown-linux-gnu-"
# TOOLCHAIN_NAME="toolchain-mips64-unknown-linux-gnu"

#
SRC_APATH=$PWD
DST_APATH=${PWD}/destdir/${TARGET}
TOOLCHAIN_PATH="${TOOLCHAIN_HOME}/${TOOLCHAIN_NAME}"

##
test -d  "$DST_APATH" && rm -rf  "$DST_APATH"
test -d "$BUILD_PATH" && rm -rf "$BUILD_PATH"
mkdir -p $BUILD_PATH


##
cd $BUILD_PATH && {
    notice "Start build project ..."
###############################################################################
#
run_cmd $SRC_APATH/configure --prefix='' --with-sysroot=/ \
    --target=$TARGET

#
run_cmd make -j$(nproc)

#
run_cmd make install DESTDIR=$DST_APATH

###############################################################################
    notice "Project build successful!"
cd - >/dev/null; }
