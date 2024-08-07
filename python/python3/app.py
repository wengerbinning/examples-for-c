#!/usr/bin/env python3

import os
import re
import shutil
import argparse




def app_install(rootfs, sysroot):
    #
    if not os.path.exists(rootfs):
        print("app is exist")
        return 0
    #
    if not os.path.exists(sysroot):
        os.makedirs(sysroot)
    #
    for home, dires, files in os.walk(rootfs):
        home = re.sub("/*$", "", home)
        #
        for each in dires:
            srcpath = home + "/" + each
            dstpath = sysroot + re.sub(rootfs + "/*", "/", srcpath)
            #
            if os.path.exists(dstpath):
                continue
            #
            if os.path.islink(srcpath):
                link = os.readlink(srcpath)
                os.symlink(link, dstpath)
            else:
                os.mkdir(dstpath, 0o755)
        #
        for each in files:
            srcpath = home + "/" + each
            dstpath = sysroot + re.sub(rootfs + "/*", "/", srcpath)
            #
            if os.path.exists(dstpath):
                continue
            #
            if os.path.islink(srcpath):
                link = os.readlink(srcpath)
                os.symlink(link, dstpath)
            else:
                shutil.copy(srcpath, dstpath)

# Entry
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog = "apps",
        description = "install apps",
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
        "-f", "--force",
        action = "store_false",
    )
    parser.add_argument(
        "rootfs",
        action = "store",
        help = "dest directory",
        default = 0
    )
    parser.add_argument(
        "sysroot",
        action = "store",
        help = "rootfs directory",
        default = 0
    )
    #
    args = parser.parse_args()
    force = vars(args)["force"]
    rootfs = vars(args)["rootfs"]
    rootfs = re.sub("/*$", "", rootfs)
    sysroot = vars(args)["sysroot"]
    sysroot = re.sub("/*$", "", sysroot)

    app_install(rootfs, sysroot)



