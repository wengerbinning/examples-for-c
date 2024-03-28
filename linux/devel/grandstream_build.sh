#!/bin/bash

. ../../../../../../public/build_funcs.sh

DEV=$1

MODULE_PATH=$(pwd)

export TOPDIR=`pwd`
export SUBDIRS=$TOPDIR


make V=s ARCH=$ARCH CROSS_COMPILE=${CROSS_PREFIX} \
    -C $KERNEL_PATH M=$MODULE_PATH modules


cp -v devel*.ko /srv/tftp


####

make clean