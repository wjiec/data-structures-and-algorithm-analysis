#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * O(N^3)
 *
 *
 * [remove print]
 *
 *  $ time ./random_serial
 *  ./random_serial  1.36s user 0.00s system 99% cpu 1.362 total
 *
 */

int *random_serial_number(const int sequence_size);


int main(int argc, char *argv[]) {
    int *serial_number = random_serial_number(8192);

    for (int i = 0; i < 8192; ++i) {
        if (i && i % 8 == 0) {
            printf("\n");
        }
        // print number
        printf("%04d ", serial_number[i]);
    }
    // free memory
    free(serial_number);

    return 0;
}


int *random_serial_number(const int sequence_size) {
    int *serial = (int*)malloc(sizeof(int) * sequence_size);
    memset(serial, 0, sizeof(int) * sequence_size);

    srand((unsigned int)time(NULL));
    for (int i = 0, val, re_rand; i < sequence_size; ++i) { // N

        do { // 0 - (~)
            re_rand = 0;
            // random number
            val = rand() % sequence_size + 1;
            // check exists
            for (int j = 0; j < i; ++j) { // N
                if (serial[j] == val) {
                    re_rand = 1;
                    break;
                }
            }
        } while (re_rand);

        serial[i] = val;
    }

    return serial;
}
