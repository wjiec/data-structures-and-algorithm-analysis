#include <iostream>


class Gcd {
    public:
        int operator()(int x, int y);
};


int main(int argc, char *argv[]) {
    auto gcd_p = new Gcd;
    Gcd gcd;

    std::cout << "Gcd(1899, 1234) = " << (*gcd_p)(1899, 1234) << std::endl;
    std::cout << "Gcd(1234, 1899) = " << gcd(1234, 1899) << std::endl;
    std::cout << "Gcd(9125, 3395) = " << gcd(9125, 3395) << std::endl;
    std::cout << "Gcd(1989, 1690) = " << gcd(1989, 1690) << std::endl;
    std::cout << "Gcd(1989, 1590) = " << gcd(1989, 1590) << std::endl;

    return 0;
}


int Gcd::operator()(int x, int y) {
    int rem;

    while (y > 0) {
        rem = x % y;
        x = y;
        y = rem;
    }

    return x;
}
