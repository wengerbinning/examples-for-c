#!/usr/bin/env python3

import argparse


# Entry
if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        prog = "test",
        description = "defwef",
        epilog = "Copyright"
    )

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

    args = parser.parse_args()

    rootfs = vars(args)["rootfs"]
    print(rootfs)
