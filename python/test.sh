

rootfs=./rootfs
image=rootfs.img
ignore="device.table"


mkfs.jffs2 -v -q -n -b -e 128 \
    -r ${rootfs} -o ${image}

# -D ${ignore}