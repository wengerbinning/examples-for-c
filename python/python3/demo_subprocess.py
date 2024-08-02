#!/usr/bin/env python3

import os
import sys
import subprocess

if __name__ == "__main__":
    print("{0} running task {1}".format(os.getcwd(), sys.argv[0]))
    # proc = subprocess.Popen(sys.argv[0], stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell = True, text = True)
    proc = subprocess.Popen(sys.argv[0])
    # stdout, stderr = proc.communicate()
    # returncode = proc.returncode
    # # print("Normal")
    # # print(stdout)
    # print("ERROR")
    # print(stderr)
    # print(returncode)