#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#


class MaxSubSequenceSum(object):

    def __init__(self, sequence: list):
        self._sequence = sequence
        self._sum = 0
        self._left_index = 0
        self._right_index = 0

    def brute_force(self):
        for start_i, start_v in enumerate(self._sequence):
            curr_sum = 0
            for index in range(start_i, len(self._sequence)):
                curr_sum += self._sequence[index]
                if curr_sum > self._sum:
                    self._sum = curr_sum
                    self._left_index = start_i
                    self._right_index = index

    @property
    def sum(self):
        return self._sum

    @property
    def left_index(self):
        return self._left_index

    @property
    def right_index(self):
        return self._right_index


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
        bf = MaxSubSequenceSum(seq)
        bf.brute_force()
        print("{} Max sub sequence sum: {}({}, {})".format(
            seq, bf.sum, bf.left_index, bf.right_index))
