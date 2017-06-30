#include <stdio.h>
#include <stdlib.h>
#define NOT_FOUND -1


int find_gt_nd2(int *sequence, size_t sequence_size);
int find_gt_nd2_ex(int *sequence, size_t sequence_size);


int main(int argc, char *argv[]) {
    int sequence_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} :: %2d :: %2d\n",
           find_gt_nd2(sequence_1, 10), find_gt_nd2_ex(sequence_1, 10));

    int sequence_2[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    printf("{0, 1, 0, 1, 0, 1, 0, 1, 0, 1} :: %2d :: %2d\n",
           find_gt_nd2(sequence_2, 10), find_gt_nd2_ex(sequence_2, 10));

    int sequence_3[] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};
    printf("{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1} :: %2d :: %2d\n",
           find_gt_nd2(sequence_3, 12), find_gt_nd2_ex(sequence_3, 12));

    int sequence_4[] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1};
    printf("{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1} :: %2d :: %2d\n",
           find_gt_nd2(sequence_4, 11), find_gt_nd2_ex(sequence_4, 11));

    int sequence_5[] = {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};
    printf("{1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0} :: %2d :: %2d\n",
           find_gt_nd2(sequence_5, 11), find_gt_nd2_ex(sequence_5, 11));

    int sequence_6[] = {1, 0, 1, 0, 1};
    printf("{1, 0, 1, 0, 1} :: %2d :: %2d\n",
           find_gt_nd2(sequence_6, 5), find_gt_nd2_ex(sequence_6, 5));

    int sequence_7[] = {1, 1, 0, 1, 0};
    printf("{1, 1, 0, 1, 0} :: %2d :: %2d\n",
           find_gt_nd2(sequence_7, 5), find_gt_nd2_ex(sequence_7, 5));
    return 0;
}


int find_gt_nd2(int *sequence, size_t sequence_size) {
    // base action
    if (sequence_size == 1) {
        return sequence[0];
    }

    int odd_cnt = 1;
    int odd_num = sequence_size % 2 ? sequence[sequence_size - 1] : NOT_FOUND;

    // build next-parameter
    size_t next_sequence_size = 0;
    int *next_sequence = (int*)malloc(sizeof(int) * sequence_size);
    for (size_t i = 0; i < sequence_size; i += 2) {
        if (sequence[i] == sequence[i + 1]) {
            next_sequence[next_sequence_size++] = sequence[i];

            if (odd_num != NOT_FOUND && odd_num == sequence[i]) {
                ++odd_cnt;
            }
        }
    }

    // is last element in odd sequence
    if (odd_cnt > (next_sequence_size + 1) / 2) {
        return odd_num;
    }

    // cannot found the same element
    if (next_sequence_size == 0) {
        if (odd_num != NOT_FOUND) {
            return odd_num;
        }
        return NOT_FOUND;
    }

    // find next sequence
    int result = find_gt_nd2(next_sequence, next_sequence_size);

    // free memory
    free(next_sequence);

    // sub-sequence not found
    if (result == NOT_FOUND) {
        return NOT_FOUND;
    }

    // check result is valid
    int count = 0;
    for (size_t i = 0; i < sequence_size; ++i) {
        if (sequence[i] == result) {
            ++count;
        }
    }

    // found
    if (count > sequence_size / 2) {
        return result;
    }

    // not found
    return NOT_FOUND;
}

// is bad[O(N^2)]
int find_gt_nd2_ex(int *sequence, size_t sequence_size) {
    size_t array_size = 0;
    int *key = (int*)malloc(sizeof(int) * sequence_size);
    int *cnt = (int*)malloc(sizeof(int) * sequence_size);

    for (int i = 0; i < sequence_size; ++i) {
        int flag = 0;
        for (int j = 0; j < array_size; ++j) {
            if (sequence[i] == key[j]) {
                ++cnt[j];
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            key[array_size] = sequence[i];
            cnt[array_size++] = 1;
        }
    }

    int result = NOT_FOUND;
    for (int i = 0; i < array_size; ++i) {
        if (cnt[i] > sequence_size / 2) {
            result = key[i];
            break;
        }
    }

    free(key);
    free(cnt);

    return result;
}
