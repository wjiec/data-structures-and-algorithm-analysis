#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#


def gcd(x, y):
    while y > 0:
        x, y = y, x % y
    return x


if __name__ == '__main__':
    print("Gcd(1899, 1234) = {}".format(gcd(1899, 1234)))
    print("Gcd(1234, 1899) = {}".format(gcd(1234, 1899)))
    print("Gcd(9125, 3395) = {}".format(gcd(9125, 3395)))
    print("Gcd(1989, 1690) = {}".format(gcd(1989, 1690)))
    print("Gcd(1989, 1590) = {}".format(gcd(1989, 1590)))
