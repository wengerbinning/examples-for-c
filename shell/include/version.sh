#!/usr/bin/env bash

# VERSION STRING FORMAT:
#	-1- major.minor
#   -2- major.minor.patch
# when VER_STRICT != true and released is number and released << 255:
#	-3-	major.minor.patch.released
# else
#   -4- major.minor.patch-released

# CONTROL VRIABLE:
# 
# VER_PATCH:int    - Change defult VERSION PATCH
# RELEASED:string  - Change defult VERSION RELEASED
# VER_PREFIX:char  - Setting VERSION PREFIX
# VER_STRICT:bool  - Control VERSION STRING FORMAT (default: false)
# VER_MASK:int	   - Control VERSION MASK (default: 0xE)
#						major:0x8 minor:0x4 patch:0x2 released:0x1

# APIs:
#
# Build version string:
#	-1- version <major> <minor> [<patch>] [<released>]
#		Print version string. 
#
# Parsing version string: 
#	-1- ver_major <version>
#		Print version major
#	-2- ver_minor <version>
#		Print version minor
#	-3- ver_patch <version>
#		Print version patch
#	-4- ver_released <version>
#		Print version released
#
# Operating version:
#	-1- ver_cmp_high <old version> <new version> [<version mask>]
#		Comparing whether the new version  is a higher than the old version.
#	-2- ver_cmp_low <old version> <new version> [<version mask>]
#		Comparing whether the new version is a lower than the old version.
#   -3- ver_equal <old version> <new version> [<version mask>]
#		Compiling whether the new version is equal  to the old version.  

# DEPENDS:
#
# cut ver_major,ver_minor,ver_patch,ver_released
# tr  ver_patch,ver_released
# wc  ver_patch,ver_released

# usage: version <major> <minor> [<patch>] [<released>]
version() {
	local ver major minor patch released
	case $# in
	0|1)
		echo "version <major> <minor> [<patch>] [<released>]"
		return;;
	2)
		major=$1; minor=$2; patch=${VER_PATCH:-}; released=${RELEASED}
		;;
	3)
		major=$1; minor=$2; patch=$3; released=${RELEASED} 
		;;
	*)
		major=$1; minor=$2; patch=$3; released=$4 
	esac
	if [ -n "$patch" -a "$patch" != 0 ]; then
		ver="${VER_PREFIX}$major.$minor.$patch"
	else
		ver="${VER_PREFIX}$major.$minor"
	fi
	if [ -n "$released" ]; then
		if [ "$VER_STRICT" != true -a "$released" == $((released)) -a "$released" -le 255 ]; then
			ver=${ver:+$ver.$released}
		else
			ver=${ver:+$ver-$released}
		fi
	fi
	echo $ver	
}

# usage: ver_major <version>
ver_major() {
	local ver=${1#*v} major prefix
	major=$(echo $ver | cut -d'.' -f1)
	prefix=${VER_PREFIX:-V}
	echo ${major#*$prefix}
}

# usage: ver_minor <version>
ver_minor() {
	local ver=${1#*v} minor
	minor=$(echo $ver | cut -d'.' -f2)
	echo $minor
}

# usage: ver_patch <version>
ver_patch() {
	local ver=${1%%-*} cnt patch=0
	cnt=$(echo $ver | tr -s '.' ' ' | wc -w)
	if [ "$cnt" -ge 3 ]; then
		patch=$(echo ${ver} | cut -d'.' -f3)
	fi
	echo $patch
}

# usage: ver_major <version>
ver_released() {
	local ver=$1 cnt released
	if [ $ver != ${ver%%-*} ]; then
		released=${ver#*-}
	elif [ "$VER_STRICT" != true ]; then
		cnt=$(echo $ver | tr -s '.' ' ' | wc -w)
		if [ "$cnt" -ge 4 ]; then
			released=$(echo $ver | cut -d'.' -f4)
		fi
	fi
	test -n "$released" && echo "$released"
}
