#!/usr/bin/env bash


pid=$(ps -e | grep [h]elloworld | cut -d' ' -f2)
test -n "$pid" || exit

#
cat /proc/$pid/status
#
# VmHWM(high water mark):  驻留内存的峰值
# VmRSS(Resident set size): 驻留内存的大小
# RssAnon: 匿名驻留内存。
# RssFile: 文件隐射驻留内存。
# RssShmem: 共享驻留内存。
# 
# VmData:
# VmStk
# VmExe
# VmLib
# VmPTE
# VmPMD
# VmSwap





#
# cat /proc/$pid/statm
# size: 程序总大小
# resident： 驻留内存
# shared：
# text：
# lib：
# data：
