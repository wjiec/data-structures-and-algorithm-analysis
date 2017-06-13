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

    def divide_and_conquer(self):
        self._sum = self._do_divide_and_conquer(0, len(self._seq) - 1)

    def _do_divide_and_conquer(self, left_index: int, right_index: int):
        # base case
        if left_index == right_index:
            return self._seq[left_index]

        center_index = (left_index + right_index) // 2
        left_max_sum = self._do_divide_and_conquer(left_index, center_index)
        right_max_sum = self._do_divide_and_conquer(center_index + 1,
                                                    right_index)

        # left border
        left_border_max_sum = self._seq[center_index]
        left_border_sum = 0
        for index in range(center_index, left_index - 1, -1):
            left_border_sum += self._seq[index]
            if left_border_sum > left_border_max_sum:
                left_border_max_sum = left_border_sum

        # right border
        right_border_max_sum = self._seq[center_index + 1]
        right_border_sum = 0
        for index in range(center_index + 1, right_index + 1):
            right_border_sum += self._seq[index]
            if right_border_sum > right_border_max_sum:
                right_border_max_sum = right_border_sum

        # merge result
        left_and_right_max_sum = left_border_max_sum + right_border_max_sum
        if left_and_right_max_sum > left_max_sum \
                and left_and_right_max_sum > right_max_sum:
            return left_and_right_max_sum
        elif left_max_sum > left_and_right_max_sum \
                and left_max_sum > right_max_sum:
            return left_max_sum
        else:
            return right_max_sum

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
        divide.divide_and_conquer()
        print("{} Max sub sequence sum: {}".format(seq, divide.sum))
