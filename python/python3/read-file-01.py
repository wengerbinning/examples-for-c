#!/usr/bin/env python3

try:
    with open("hello.txt") as file:
        print(file.read())

except FileNotFoundError:
    print("not found")

else:
    print("normal")

finally:
    print("finished")