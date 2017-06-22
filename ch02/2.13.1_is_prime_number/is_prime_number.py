#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#
import math
import random


def is_prime_number(number: int) -> bool:
    for i in range(2, int(math.sqrt(number))):
        if number % i == 0:
            return False
    return True


if __name__ == '__main__':
    for i in range(10):
        for j in range(99999):
            is_prime_number(random.randint(2, 9999999))
