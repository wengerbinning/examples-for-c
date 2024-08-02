#!/usr/bin/env python3

import os
import sys
import subprocess

if __name__ == "__main__":
    print("running task {1} in {0}".format(os.getcwd(), sys.argv[0]))
    proc = subprocess.Popen(sys.argv[0])
