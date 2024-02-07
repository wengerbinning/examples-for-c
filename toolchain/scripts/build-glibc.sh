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

CC=${CROSS_PREFIX}gcc

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

cd $BUILD_DIR && {
	#
	cat > config.cache <<EOF
libc_cv_forced_unwind=yes
libc_cv_c_cleanup=yes
libc_cv_arm_tls=yes

EOF
	#
	notice "Step 0 ...."
	$SOURCE_DIR/configure --prefix=$DEST_DIR \
		--target=$TARGET \
		--with-headers=$TOOLCHAIN_DIR/include \
		--disable-multilib \

		# --cache-file=config.cache \
		# --witch-binutils=$TOOLCHAIN_DIR/bin \
		# --disable-profile \
		# --enable-add-ons \


	#
	# make install-bootstrap-headers=yes install-headers

	#
	# make -j4 csu/subdir_lib

	#
	# install csu/crt1.o csu/crti.o csu/crtn.o "$TOOLCHAIN_DIR/lib"
	# ${CC} -nostdlib -nostartfiles -shared -x c /dev/null -o "$TOOLCHAIN_DIR/lib/libc.so"
	# touch "$TOOLCHAIN_DIR/include/gnu/stubs.h"

	#
	make -j4

	#
	make install DESTDIR=$DEST_DIR

	#
	cd - >/dev/null
}
