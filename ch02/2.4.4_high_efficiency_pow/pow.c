#include <stdio.h>

unsigned long long high_pow(const int x, const int n);


int main(int argc, char *argv[]) {
    printf("Pow(2, 11) = %lld\n", high_pow(2, 11));
    printf("Pow(2, 22) = %lld\n", high_pow(2, 22));
    printf("Pow(2, 23) = %lld\n", high_pow(2, 23));
    printf("Pow(2, 24) = %lld\n", high_pow(2, 24));
    printf("Pow(2, 25) = %lld\n", high_pow(2, 31));

    return 0;
}


unsigned long long high_pow(const int x, const int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return x;
    }

    if (n % 2 == 0) {
        return high_pow(x * x, n / 2);
    } else {
        return high_pow(x * x, (n - 1) / 2) * n;
    }
}
