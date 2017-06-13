#include <stdio.h>

struct max_sum {
    int sum;
    int left_index;
    int right_index;
};


struct max_sum max_sub_sequence_sum(const int sequence[], size_t sequence_size);
static struct max_sum do_max_sub_sequence_sum(const int sequence[], int left_index, int right_index);

int main(int argc, char *argv[]) {
    int sequences[][8] = {
            { 4, -3, 5, -2, -1, 2, 6, -2 },
            { 1, 2, 3, 4, -4, -3, -2, -1 },
            { 1, -1, 2, -2, 3, -3, 4, -4 },
            { 1, -1, 1, -1, 1, -1, 1, -1 },
            { 1, 2, 3, 4, 5, 6, 7, -1000 },
            { -100, 1, 2, 3, 4, 5, -9, 1 }
    };

    for (int i = 0; i < sizeof(sequences) / sizeof(sequences[0]); ++i) {
        int *sequence = sequences[i];
        struct max_sum max_sum = max_sub_sequence_sum(sequence, sizeof(sequences[0]) / sizeof(int));

        printf("Max sub sequence sum: %d(%d - %d)\n", max_sum.sum, max_sum.left_index, max_sum.right_index);
    }

    return 0;
}


/**
 * find max sub sequence sum and return
 * @param sequence
 * @param sequence_size
 * @return
 */
struct max_sum max_sub_sequence_sum(const int sequence[], size_t sequence_size) {
    return do_max_sub_sequence_sum(sequence, 0, sequence_size - 1);
}

/**
 * find max sub sequence sum by divide-and-conquer
 *
 * @param sequence
 * @param left_index
 * @param right_index
 * @return
 */
static struct max_sum do_max_sub_sequence_sum(const int sequence[], int left_index, int right_index) {
    // base case
    if (left_index == right_index) {
        struct max_sum base_case = {sequence[left_index], left_index, right_index};
        return base_case;
    }

    int center_index = (left_index + right_index) / 2;
    struct max_sum left_max_sum = do_max_sub_sequence_sum(sequence, left_index, center_index);
    struct max_sum right_max_sum = do_max_sub_sequence_sum(sequence, center_index + 1, right_index);

    // calc left border max sum
    struct max_sum left_border_max_sum = {sequence[center_index], center_index, center_index};
    for (int i = center_index, left_border_sum = 0; i >= left_index; --i) {
        left_border_sum += sequence[i];
        if (left_border_sum > left_border_max_sum.sum) {
            left_border_max_sum.sum = left_border_sum;
            left_border_max_sum.left_index = i;
        }
    }

    // calc right border max sum
    struct max_sum right_border_max_sum = {sequence[center_index + 1], center_index + 1, center_index + 1};
    for (int i = center_index + 1, right_border_sum = 0; i <= right_index; ++i) {
        right_border_sum += sequence[i];
        if (right_border_sum > right_border_max_sum.sum) {
            right_border_max_sum.sum = right_border_sum;
            right_border_max_sum.right_index = i;
        }
    }

    // calc result and return
    int left_and_right_max_sum = left_border_max_sum.sum + right_border_max_sum.sum;
    if (left_and_right_max_sum > left_max_sum.sum && left_and_right_max_sum > right_max_sum.sum) {
        struct max_sum result = {left_and_right_max_sum, left_border_max_sum.left_index, right_border_max_sum.right_index};
        return result;
    } else if (left_max_sum.sum > left_and_right_max_sum && left_max_sum.sum > right_max_sum.sum) {
        return left_max_sum;
    } else {
        return right_max_sum;
    }
}
