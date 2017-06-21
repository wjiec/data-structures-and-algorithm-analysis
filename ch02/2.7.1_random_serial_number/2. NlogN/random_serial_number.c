#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * gcc -Wall -std=c99 -o serial_number random_serial_number.c
 *
 * [remove print]
 * $ time ./serial_number
 * ./serial_number  0.00s user 0.00s system 43% cpu 0.009 total
 * ./serial_number  0.00s user 0.00s system 29% cpu 0.013 total
 * ./serial_number  0.00s user 0.00s system 63% cpu 0.013 total
 *
 */
int *random_serial_number(const int size);


int main(int argc, char *argv[]) {
    int *serial_number = random_serial_number(8192);

    for (int i = 0; i < 8192; ++i) {
        if (i && i % 8 == 0) {
            printf("\n");
        }
        printf("%-6d", serial_number[i]);
    }
    free(serial_number);

    return 0;
}


int *random_serial_number(const int size) {
    int *serial_number = (int*)malloc(sizeof(int) * size);
    int *used_number = (int*)malloc(sizeof(int) * size);
    memset(serial_number, 0, sizeof(int) * size);
    memset(used_number, 0, sizeof(int) * size);

    srand((unsigned)time(NULL));
    for (int i = 0, val; i < size; ++i) { // N
        val = rand() % size + 1;

        while (used_number[val] == 1) { // logN
            // re-random
            val = rand() % size + 1;
        }

        serial_number[i] = val;
        used_number[val] = 1;
    }

    free(used_number);
    return serial_number;
}
