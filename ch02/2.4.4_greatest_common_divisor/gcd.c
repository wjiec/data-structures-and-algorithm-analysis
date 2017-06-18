#include <stdio.h>

int gcd(int x, int y);


int main(int argc, char *argv[]) {
    printf("Gcd(1899, 1234) = %d\n", gcd(1899, 1234));
    printf("Gcd(1234, 1899) = %d\n", gcd(1234, 1899));
    printf("Gcd(9125, 3395) = %d\n", gcd(9125, 3395));
    printf("Gcd(1989, 1690) = %d\n", gcd(1989, 1690));
    printf("Gcd(1989, 1590) = %d\n", gcd(1989, 1590));

    return 0;
}


int gcd(int x, int y) {
    int rem;

    while (y > 0) {
        rem = x % y;
        x = y;
        y = rem;
    }

    return x;
}
