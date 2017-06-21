#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * gcc -Wall -std=c99 -o serial_number random_serial_number.c
 *
 * [remove print]
 * $ time ./serial_number
 * ./serial_number  0.00s user 0.00s system 0% cpu 0.004 total
 * ./serial_number  0.00s user 0.00s system 0% cpu 0.008 total
 * ./serial_number  0.00s user 0.00s system 0% cpu 0.005 total
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

    for (int i = 0; i < size; ++i) {
        serial_number[i] = i + 1;
    }

    srand((unsigned)time(NULL));
    // swap element
    for (int i = 0, tmp, rand_index; i < size; ++i) {
        rand_index = rand() % size;

        tmp = serial_number[i];
        serial_number[i] = serial_number[rand_index];
        serial_number[rand_index] = tmp;
    }

    return serial_number;
}
