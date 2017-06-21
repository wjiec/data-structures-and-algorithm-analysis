#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#
import random


def random_serial_number(size: int):
    serial_number = []

    for i in range(size):
        while True:
            val = random.randint(0, size) + 1
            if val not in serial_number:
                break
        serial_number.append(val)
    return serial_number

if __name__ == '__main__':
    random_serial_number(8192)
