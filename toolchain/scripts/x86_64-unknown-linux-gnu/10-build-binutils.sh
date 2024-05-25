#!/usr/bin/env bash

##
error() {
    echo -en "\e[31m"; echo $@; echo -en "\e[0m"
}
#
warning() {
    echo -en "\e[33m"; echo $@; echo -en "\e[0m"
}
#
notice() {
    echo -en "\e[32m"; echo $@; echo -en "\e[0m"
}
#
note() {
    echo -en "\e[34m"; echo $@; echo -en "\e[0m"
}
#
debug() {
    echo -en "\e[32m"; echo $@; echo -en "\e[0m"
}
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
TOOLCHAIN_NAME="toolchain-x86_64-unknown-linux-gnu"
TOOLCHAIN_PATH="${TOOLCHAIN_HOME}/${TOOLCHAIN_NAME}"
#
ARCH=x86_64
TARGET="x86_64-unknown-linux-gnu"
CROSS_PREFIX="x86_64-unknown-linux-gnu-"

##
BUILD_PATH=".build"
SRC_APATH=$PWD
DST_APATH=${PWD}/destdir

##
test -d  "$DST_APATH" && rm -rf  "$DST_APATH"
test -d "$BUILD_PATH" && rm -rf "$BUILD_PATH"
mkdir -p $BUILD_PATH


##
cd $BUILD_PATH && {
	notice "Start build project ..."
###############################################################################

#
run_cmd $SRC_APATH/configure --prefix='' \
	--target=$TARGET \
	--with-sysroot=/ \

#
run_cmd make -j$(nproc)

#
run_cmd make install DESTDIR=$DST_APATH

###############################################################################
	cd - </dev/null
	notice "Project build successful!"
}
