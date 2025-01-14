#!/usr/bin/env bash

##
error()   { echo -en "\e[31m"; echo -en $@; echo -en "\e[0m\n"; }
warning() { echo -en "\e[33m"; echo -en $@; echo -en "\e[0m\n"; }
notice()  { echo -en "\e[32m"; echo -en $@; echo -en "\e[0m\n"; }
note()    { echo -en "\e[34m"; echo -en $@; echo -en "\e[0m\n"; }
debug()   { echo -en "\e[32m"; echo -en $@; echo -en "\e[0m\n"; }

#
run_cmd() {
	local idx=${_cmd_count:-0}
	eval "cmd_${idx}_timestamp=\"$(date)\""
	eval "cmd_${idx}_cmdline=\"$@\""
	_cmd_count=$((idx + 1))
	note "running command:\e[0m $@"
	eval "$@"
	test $? -ne 0 && {
		error "running command error!"
		debug "command:$@"
		exit 1
	}
}
#
cmd_total() {
	local idx=0 stamp1 stamp2
	local timestamp cmdline
	while [ $idx -lt ${_cmd_count:-0} ]; do
		eval "timestamp=\$cmd_${idx}_timestamp"
		eval "cmdline=\$cmd_${idx}_cmdline"
		stamp1=$(date -d"$timestamp"  +%s)
		stamp2=$(date +%s)
		printf "[%s] \033[1;3m%s\033[0m expend %d seconds\n" "${timestamp}" "${cmdline}" $((stamp2 - stamp1))
		idx=$((idx + 1))
	done
}

##
# #
# ARCH=x86
# TARGET="x86-unknown-linux-gnu"
# CROSS_PREFIX="x86-unknown-linux-gnu-"
# #
# ARCH=x86_64
# TARGET="x86_64-unknown-linux-gnu"
# CROSS_PREFIX="x86_64-unknown-linux-gnu-"

# #
# ARCH=arm
# TARGET="arm-unknown-linux-gnu"
# CROSS_PREFIX="arm-unknown-linux-gnu-"
# #
# ARCH=arm64
# TARGET="arm64-unknown-linux-gnu"
# CROSS_PREFIX="arm64-unknown-linux-gnu-"

# #
# ARCH=mips
# TARGET="mips-unknown-linux-gnu"
# CROSS_PREFIX="mips-unknown-linux-gnu-"
# #
# ARCH=mips64
# TARGET="mips64-unknown-linux-gnu"
# CROSS_PREFIX="mips64-unknown-linux-gnu-"
#
#
TOOLCHAIN_HOME="/opt/toolchains"
TOOLCHAIN_NAME="toolchain-${TARGET}"
TOOLCHAIN_PATH="${TOOLCHAIN_HOME}/${TOOLCHAIN_NAME}"

##
WORKPATH=".build"
SRC_PATH=$PWD
DST_PATH=${PWD}/dest
#
test -d "$DST_PATH" && mv -f $DST_PATH ${DST_PATH}.old
test -d "$WORKPATH" && rm -rf "$WORKPATH"
test -d "$WORKPATH" || mkdir -p $WORKPATH
cd $WORKPATH && {
    notice "Start build project ..."
###############################################################################
#
run_cmd $SRC_PATH/configure --prefix='' --with-sysroot=/ \
    --target=$TARGET

#
run_cmd make -j$(nproc)

#
run_cmd make install DESTDIR=$DST_PATH

###############################################################################
	cd - </dev/null
	cmd_total
	notice "Project build successful!"
}
