#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>


class IsPrimeNumber {
    public:
        bool operator()(const int number);
};


int main(int argc, char *argv[]) {
    IsPrimeNumber prime_number_checker;
    struct timeval start, end;

    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; ++i) {
        gettimeofday(&start, nullptr);
        for (int j = 0; j < 9999999; ++j) {
            prime_number_checker(std::rand());
        }
        gettimeofday(&end, NULL);
        std::printf("[%d]Running time: %d us\n", i, 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);
    }

    return 0;
}

bool IsPrimeNumber::operator()(const int number) {
    auto end = (int)std::sqrt(number);

    for (int i = 2; i < end; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}
