#!/usr/bin/env python


# https://peps.python.org/pep-3107/



'''
parameter [:expression] [=default]

int
list
tuple
str

"description"


'''



def func(param1: int , param2: bool):
    print(param1)
    print( type(param2))



func(1, 2)



print(bool(None))