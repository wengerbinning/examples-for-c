VER_MIN=$1
VER_MAX=255


VER_FMT0="%d"
VER_FMT1="%03d"
VER_FMT=${VER_FMT:-$VER_FMT0}

VER_MAJOR_FMT=${VER_MAJOR_FMT:-$VER_FMT}
VER_MINOR_FMT=${VER_MINOR_FMT:-$VER_FMT}
VER_PATCH_FMT=${VER_PATCH_FMT:-$VER_FMT}

VER_SFORMAT0="${VER_MAJOR_FMT0:-$VER_FMT0}.${VER_MINOR_FMT0:-$VER_FMT0}.${VER_PATCH_FMT0:-$VER_FMT0}"
VER_SFORMAT="${VER_MAJOR_FMT:-$VER_FMT}.${VER_MINOR_FMT:-$VER_FMT}.${VER_PATCH_FMT:-$VER_FMT}"

VERSION_SPREFIX="v"
VERSION_SFORMAT=${VERSION_SFORMAT:-$VER_SFORMAT}

VERSION_CFORMAT0="%02X%02X%2X%2X"

VER_CFMT="0x%06X"


VER_MAJOR=0
VER_MINOR=0
VER_PATCH=0


ver_int_inc() {
	local val=${1:-$VER_MIN} fmt=${2:-$VER_MAJOR_FMT}
	val=$(((val + 1) % VER_MAX)); 
	printf $fmt $val
}




ver_major_inc() {
	local major=${1:-$VER_MAJOR} fmt=${2:-$VER_MAJOR_FMT}
	major=$(ver_int_inc $major)
	printf $fmt $major
}





version_inc() {
	local vcode=${1:-$VERSION_CODE}; fmt=${2:-$VER_CFMT} 
	local major minor patch
	vcode=$(printf $fmt $vcode)
	printf "$VER_CFMT" $vcode

}





version_inc $1
