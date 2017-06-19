#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#


def high_pow(x, y):
    if y == 0:
        return 1
    if y == 1:
        return x
    if y % 2 == 0:
        return high_pow(x * x, y / 2)
    else:
        return high_pow(x * x, (y - 1) / 2) * x


if __name__ == '__main__':
    print("high_pow(2, 11) = {}".format(high_pow(2, 11)))
    print("high_pow(2, 22) = {}".format(high_pow(2, 22)))
    print("high_pow(2, 33) = {}".format(high_pow(2, 33)))
    print("high_pow(2, 44) = {}".format(high_pow(2, 44)))
    print("high_pow(2, 55) = {}".format(high_pow(2, 55)))
    print("high_pow(2, 66) = {}".format(high_pow(2, 66)))
    print("high_pow(2, 77) = {}".format(high_pow(2, 77)))
    print("high_pow(2, 88) = {}".format(high_pow(2, 88)))
    print("high_pow(2, 99) = {}".format(high_pow(2, 99)))
