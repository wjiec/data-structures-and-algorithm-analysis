#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#
from functools import reduce


class MaxSubSequenceSum(object):

    def __init__(self, sequence: list):
        self._seq = sequence
        self._sum = sequence[0]
        self._left_index = 0
        self._right_index = 0

    def calc(self):
        def _swap(s, v):
            s += v
            if (s > self._sum):
                self._sum = s
            elif s < 0:
                s = 0
            return s
        reduce(_swap, self._seq)

    @property
    def sum(self):
        return self._sum


if __name__ == '__main__':
    sequences = [
        [4, -3, 5, -2, -1, 2, 6, -2],
        [1, 2, 3, 4, -4, -3, -2, -1],
        [1, -1, 2, -2, 3, -3, 4, -4],
        [1, -1, 1, -1, 1, -1, 1, -1],
        [1, 2, 3, 4, 5, 6, 7, -1000],
        [-100, 1, 2, 3, 4, 5, -9, 1]
    ]

    for seq in sequences:
        divide = MaxSubSequenceSum(seq)
        divide.calc()
        print("{} Max sub sequence sum: {}".format(seq, divide.sum))
