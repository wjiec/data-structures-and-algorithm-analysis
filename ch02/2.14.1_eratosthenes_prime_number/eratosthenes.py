#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#
import math


def eratosthenes_sequence(size: int):
    ret = [2] + list(range(3, size, 2))
    _size_range = range(2, size)

    for val in ret:
        if val > math.sqrt(size):
            break

        for i in _size_range:
            if i * val > size:
                break

            try:
                ret.remove(i * val)
            except ValueError:
                pass
    return ret


if __name__ == '__main__':
    print(eratosthenes_sequence(100))
