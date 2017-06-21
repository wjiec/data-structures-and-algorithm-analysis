#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


/**
 * g++ -Wall -std=c++11 -o serial_number random_serial_number.cc
 *
 * [remove print]
 * $ time ./serial_number
 * ./serial_number  0.00s user 0.00s system 37% cpu 0.011 total
 * ./serial_number  0.00s user 0.00s system 41% cpu 0.010 total
 * ./serial_number  0.00s user 0.00s system 31% cpu 0.013 total
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
    std::vector<int> used(size, 0);

    std::srand((unsigned)time(nullptr));
    for (int i = 0, val; i < size; ++i) { // N
        do {
            val = std::rand() % size + 1; // logN
        } while (used[val - 1] == 1);

        serial.push_back(val);
        used[val] = 1;
    }
}
