#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#
import random


def random_serial_number(size: int) -> list:
    serial_number = [i for i in range(1, size + 1)]

    for i, v in enumerate(serial_number):
        rand = random.randint(0, size)
        serial_number[i], serial_number[rand] = serial_number[rand], serial_number[i]
    return serial_number


if __name__ == '__main__':
    for number in random_serial_number(8192):
        print("{:6}".format(number), end='')
