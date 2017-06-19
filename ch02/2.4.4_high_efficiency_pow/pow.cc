#include <iostream>


class Pow {
    public:
        int operator()(const int x, const int n);
};


int main(int argc, char *argv[]) {
    auto pow_p = new Pow;
    Pow pow;

    std::cout << "Pow(2, 11) = " << (*pow_p)(2, 11) << std::endl;
    std::cout << "Pow(2, 12) = " << pow(2, 12) << std::endl;
    std::cout << "Pow(2, 13) = " << pow(2, 13) << std::endl;
    std::cout << "Pow(2, 14) = " << pow(2, 14) << std::endl;
    std::cout << "Pow(2, 15) = " << pow(2, 15) << std::endl;

    return 0;
}


int Pow::operator()(const int x, const int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return x;
    }

    if (n % 2 == 0) {
        return operator()(x * x, n / 2);
    } else {}
    return operator()(x * x, (n - 1) / 2) * x;
}
