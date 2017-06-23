#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int* sequence_t;
sequence_t make_sequence(const int size);
void print_sequence(const sequence_t sequence, const int size);
static int get_sequence_element(const sequence_t sequence, const int index);
static void set_sequence_element(sequence_t sequence, const int index);


int main(int argc, char *argv) {
    sequence_t sequence = make_sequence(999999999);
    print_sequence(sequence, 99999999);

    return 0;
}

sequence_t make_sequence(const int size) {
    int byte_size = size / 32 + (size % 32 == 0 ? 0 : 1);
    sequence_t sequence = (sequence_t)malloc((unsigned)byte_size * sizeof(int));
    memset(sequence, 0, (unsigned)byte_size * sizeof(int));

    for (int i = 2, e = (int)sqrt(size); i < e; ++i) {
        if (get_sequence_element(sequence, i) != 0) {
            continue;
        }

        for (int j = i * 2; j < size; j += i) {
            //       ^^^^^ here
            set_sequence_element(sequence, j);
        }
    }

    return sequence;
}

void print_sequence(const sequence_t sequence, const int size) {
    for (int i = 2; i < 100; ++i) {
        if (get_sequence_element(sequence, i) == 0) {
            printf("%-10d", i);
        }
    }
}

static int get_sequence_element(const sequence_t sequence, const int index) {
    int byte_index = index / 32;
    int bit_offset = index % 32 + 1;

    return ((unsigned)sequence[byte_index] & (1 << bit_offset)) >> bit_offset;
}

static void set_sequence_element(sequence_t sequence, const int index) {
    int byte_index = index / 32;
    int bit_offset = index % 32 + 1;

    sequence[byte_index] |= (unsigned)1 << bit_offset;
}
