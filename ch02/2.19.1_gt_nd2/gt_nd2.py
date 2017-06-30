#!/usr/bin/env python
#
# Copyright (C) 2017 ShadowMan
#


def find_gt_nd2(sequence: list) -> int:
    if len(sequence) == 1:
        return sequence[0]

    odd_num = sequence[-1] if len(sequence) % 2 else -1
    odd_cnt = 1 if len(sequence) % 2 else 0

    sub_sequence = list()
    for i in range(0, len(sequence) - odd_cnt, 2):
        if sequence[i] == sequence[i + 1]:
            sub_sequence.append(sequence[i])

            if sequence[i] == odd_num:
                odd_cnt += 1

    if odd_num != -1 and odd_cnt > (len(sub_sequence) + 1) // 2:
        return odd_num

    if len(sub_sequence) == 0:
        if odd_num != -1:
            return odd_num
        return -1

    result = find_gt_nd2(sub_sequence)
    result_cnt = 0
    for el in sequence:
        if el == result:
            result_cnt += 1
    if result_cnt > len(sequence) // 2:
        return result
    return -1


if __name__ == '__main__':
    sequences = [
        [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
        [0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
        [0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1],
        [0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1],
        [1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0],
        [1, 0, 1, 0, 1],
        [1, 1, 0, 1, 0],
    ]

    for seq in sequences:
        print(seq, find_gt_nd2(seq))
