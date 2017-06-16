#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#


class BinarySearch(object):

    def __init__(self, sequence):
        self._sequence = sequence

    def search(self, element):
        start = 0
        end = len(self._sequence) - 1

        while start <= end:
            center = (start + end) // 2

            if element > self._sequence[center]:
                start = center + 1
            elif element < self._sequence[center]:
                end = center - 1
            else:
                return center
        return -1


if __name__ == '__main__':
    searcher = BinarySearch([0, 1, 3, 5, 6, 7, 8, 9])

    print("Binary Search: {}".format(searcher.search(2)))
    print("Binary Search: {}".format(searcher.search(5)))
    print("Binary Search: {}".format(searcher.search(9)))
