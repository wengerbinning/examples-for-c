#!/bin/bash

file=${1:-/usr/include/llvm-c/Analysis.h}



while read line; do
    test -n "$line" || continue

    echo "${line}"
done  < $file