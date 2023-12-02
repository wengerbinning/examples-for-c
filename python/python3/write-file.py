#!/usr/bin/env python3

mod = open("build-module.log", "a+")

for line in mod:
  print(line)

mod.write("module13\n")
mod.write("module2\n")

mod.close()