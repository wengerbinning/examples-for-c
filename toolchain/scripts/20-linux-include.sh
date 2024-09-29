#!/usr/bin/env bash

##
error() { echo -en "\e[31m"; echo $@; echo -en "\e[0m"; }
warning() { echo -en "\e[33m"; echo $@; echo -en "\e[0m"; }
notice() { echo -en "\e[32m"; echo $@; echo -en "\e[0m"; }
note() { echo -en "\e[34m"; echo $@; echo -en "\e[0m"; }
debug() { echo -en "\e[32m"; echo $@; echo -en "\e[0m"; }
#
run_cmd() {
    eval "time $@"
    test $? -ne 0 && {
        error "running command error!"
        debug "command:$@"
        exit 1
    }
}


##
TOOLCHAIN_HOME="/opt/toolchains"
SRC_APATH=$PWD
BUILD_PATH=".build"

#
TOOLCHAIN_NAME="toolchain-x86_64-unknown-linux-gnu"

#
# ARCH=x86
# TARGET="x86-unknown-linux-gnu"
# CROSS_PREFIX="x86-unknown-linux-gnu-"
#
# ARCH=x86_64
# TARGET="x86_64-unknown-linux-gnu"
# CROSS_PREFIX="x86_64-unknown-linux-gnu-"
#
# ARCH=arm
# TARGET="arm-unknown-linux-gnu"
# CROSS_PREFIX="arm-unknown-linux-gnu-"
#
# ARCH=arm64
# TARGET="arm64-unknown-linux-gnu"
# CROSS_PREFIX="arm64-unknown-linux-gnu-"
#
ARCH=mips
TARGET="mips-unknown-linux-gnu"
CROSS_PREFIX="mips-unknown-linux-gnu-"





#
TOOLCHAIN_PATH="${TOOLCHAIN_HOME}/${TOOLCHAIN_NAME}"
DST_APATH=${PWD}/destdir/$TARGET

##
test -d  "$DST_APATH" && rm -rf  "$DST_APATH"
test -d "$BUILD_PATH" && rm -rf "$BUILD_PATH"
mkdir -p $BUILD_PATH

##
# cd $BUILD_PATH && {
	notice "Start build project ..."
###############################################################################

#
make ARCH=$ARCH headers_install INSTALL_HDR_PATH=$DST_APATH

###############################################################################
#	cd - </dev/null
	notice "Project build successful!"
# }