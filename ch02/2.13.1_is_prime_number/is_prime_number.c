#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>


bool is_prime_number(const int number);


int main(int argc, char *argv[]) {
    struct timeval start, end;
    srand((unsigned)time(NULL));

    for (int i = 0; i < 10; ++i) {
        gettimeofday(&start, NULL);
        for (int j = 0, rand_int; j < 9999999; ++j) {
            rand_int = rand();
            is_prime_number(rand_int);
        }
        gettimeofday(&end, NULL);
        printf("[%d]Running time: %d us\n", i, 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);
    }

    return 0;
}


bool is_prime_number(const int number) {
    int end = (int)sqrt(number);

    for (int i = 2; i < end; i += 1) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}
