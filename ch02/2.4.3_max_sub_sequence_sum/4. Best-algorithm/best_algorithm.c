#include <stdio.h>

int max_sub_sequence_sum(const int sequence[], size_t sequence_size);

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
        int max_sum = max_sub_sequence_sum(sequence, sizeof(sequences[0]) / sizeof(int));

        printf("Max sub sequence sum: %d\n", max_sum);
    }

    return 0;
}


/**
 * find max sub sequence sum and return
 * @param sequence
 * @param sequence_size
 * @return
 */
int max_sub_sequence_sum(const int sequence[], size_t sequence_size) {
    int max_sum = sequence[0];

    for (int curr_sum = 0, i = 0; i < sequence_size; ++i) {
        curr_sum += sequence[i];
        // swap max sum
        if (curr_sum > max_sum) {
            max_sum = curr_sum;
        } else if (curr_sum < 0) {
            curr_sum = 0;
        }
    }

    return max_sum;
}

