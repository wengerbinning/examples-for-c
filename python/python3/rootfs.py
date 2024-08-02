#!/usr/bin/env python3

import os
import argparse

rootfs_necess_dires = (
    "lib", "sbin", "bin", "usr",
    "root",
    "etc",
    "mnt"
)

# rootfs_necess_files = (
# )





# Entry
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog = "initrcd",
        description = "build rootfs",
        epilog = "Copyright @ Wenger Binning"
    )
    #
    parser.add_argument(
        "-V", "--version",
        action = "version",
        version = "%(prog)s v0.1"
    )
    parser.add_argument(
        "-v", "--verbose",
        action = "count",
        help = "verbose information",
        default = 0
    )
    parser.add_argument(
        "rootfs",
        action = "store",
        help = "rootfs directory",
        default = 0
    )
    #
    args = parser.parse_args()
    rootfs = vars(args)["rootfs"]

    #
    if not os.path.exists(rootfs):
        os.makedirs(rootfs)

    #
    oldcwd = os.getcwd()
    os.chdir(rootfs)
    curcwd = os.getcwd()

    #
    for dir in rootfs_necess_dires:
        if not os.path.exists(dir):
            os.makedirs(dir)

    #
    os.chdir(oldcwd)
    print("build pass")

    #
