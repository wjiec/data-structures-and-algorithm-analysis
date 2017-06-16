#include <stdio.h>
#define NOT_FOUND -1

typedef int position;

position binary_search(const int element, const int sequence[], const size_t sequence_size);


int main(int argc, char *argv[]) {
    int sequence[] = { 0, 2, 3, 5, 6, 7, 9 };

    printf("Binary Search: %d\n", binary_search(1, sequence, sizeof(sequence) / sizeof(sequence[0])));
    printf("Binary Search: %d\n", binary_search(3, sequence, sizeof(sequence) / sizeof(sequence[0])));
    printf("Binary Search: %d\n", binary_search(6, sequence, sizeof(sequence) / sizeof(sequence[0])));
    return 0;
}


position binary_search(const int element, const int sequence[], const size_t sequence_size) {
    position start = 0, end = sequence_size - 1;
    position center;

    while (start <= end) {
        //        ^ start may be equal to end(Found)
        center = (start + end) / 2;

        if (element > sequence[center]) {
            start = center + 1;
        } else if (element < sequence[center]) {
            end = center - 1;
        } else {
            return center;
        }
    }
    return NOT_FOUND;
}
