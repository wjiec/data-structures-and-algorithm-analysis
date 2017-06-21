#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#
import random


def random_serial_number(size: int) -> list:
    used = {}
    serial_number = []
    for index in range(size):
        val = True
        while isinstance(val, bool) or val in used:
            val = random.randint(0, size + 1)
        used[val] = True
        serial_number.append(val)
    return serial_number


if __name__ == '__main__':
    for number in random_serial_number(8192):
        print("{:6}".format(number), end='')
