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
	#
	PATH="$TOOLCHAIN_PATH/bin${PATH:+:$PATH}"
	export PATH

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
		--enable-languages=c,c++ \
		--disable-multilib \
		--disable-threads \
		--disable-nls \
		--disable-libssp \
		--disable-libgomp \
		--disable-libatomic \
		--disable-libmudflap \
		--disable-libquadmath \
		--disable-decimal-float \
		--with-sysroot=/ \
		--with-build-sysroot=$TOOLCHAIN_PATH \

	#
	run_cmd make -j$(nproc) all-gcc

	#
	run_cmd make install-gcc  DESTDIR=$DEST_APATH

	###############################################################################
		cd - </dev/null
		notice "Project build successful!"
	}