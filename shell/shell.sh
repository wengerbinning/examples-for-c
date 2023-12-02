#!/usr/bin/bash

idx=0
file="data.txt"


lcnt=$(wc -l $file | cut -d' ' -f1)
while [ $lcnt -gt 0 ]; do 
    line=$(sed -nre "$lcnt p" $file)
    prefix=$(echo $line | cut -d':' -f1)
    value=$(echo $line | cut -d':' -f2)
    case "$prefix" in
    TRANSLATION*)
        echo $value
    ;;
    esac
    lcnt=$((lcnt - 1))
done