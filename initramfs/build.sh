rootfs=${1:-initramfs}

##
check_default_dirs() {
    local dirs_1="bin sbin lib usr etc var run tmp"
    local dirs_2="sys dev proc mnt"
    local dirs_3="root var/run etc/config etc/hotplug.d"
    local dirs_4="srv db release work"

    local dirs="$dirs_1${dirs_2:+ $dirs_2}${dirs_3:+ $dirs_3}"

    for dir in $dirs; do test -d $dir || mkdir -p $dir;  done
}

# ============================================================================ #

##
test -d $rootfs && cd $rootfs && {
###################################

#
check_default_dirs

#
sudo chown -R root:root ./

#
find ./ -path ./.git -prune -o -print0 | cpio --create --null --verbose --format=newc > ../initramfs.img

#
#
sudo chown -R wenger:wenger ./

###################################
    cd - >/dev/null
}



