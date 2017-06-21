#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


/**
 * g++ -Wall -std=c++11 -o serial_number random_serial_number.cc
 *
 * [remove print]
 * $ time ./serial_number
 * ./serial_number  0.00s user 0.00s system 64% cpu 0.006 total
 * ./serial_number  0.00s user 0.00s system 29% cpu 0.014 total
 * ./serial_number  0.01s user 0.00s system 82% cpu 0.015 total
 *
 */
class RandomSerialNumber {
    public:
        void operator()(std::vector<int> &serial, const int size);
};

int main(int argc, char *argv[]) {
    RandomSerialNumber generator;
    std::vector<int> serial_number;

    generator(serial_number, 8192);
    for (auto number : serial_number) {
        std::cout << " " << number << " ";
    }

    return 0;
}


void RandomSerialNumber::operator()(std::vector<int> &serial, const int size) {
    // initializing
    for (int i = 0; i < size; i++) {
        serial.push_back(i + 1);
    }
    // init random
    std::srand((unsigned)time(NULL));
    // swap element
    for (int i = 0; i < size; ++i) {
        std::swap(serial[i], serial[std::rand() % size]);
    }
}
