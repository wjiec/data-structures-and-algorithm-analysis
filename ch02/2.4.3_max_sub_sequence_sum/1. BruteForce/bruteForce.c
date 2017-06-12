#include <stdio.h>

struct max_sum {
    int sum;
    int left_index;
    int right_index;
};


struct max_sum max_sub_sequence_sum(const int sequence[], size_t sequence_size);


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
    struct max_sum max_sum = { sequence[0], 0, 0 };

    // start position
    for (int i = 0; i < sequence_size; ++i) {
        // end position
        for (int j = 0; j < sequence_size; ++j) {
            int curr_sum = 0;
            // calc `start -> end` sum
            for (int k = i; k < j; ++k) {
                curr_sum += sequence[k];
            }
            // check current sum bigger than max sum
            if (curr_sum > max_sum.sum) {
                max_sum.sum = curr_sum;
                max_sum.left_index = i;
                max_sum.right_index = j;
            }
        }
    }

    return max_sum;
}
