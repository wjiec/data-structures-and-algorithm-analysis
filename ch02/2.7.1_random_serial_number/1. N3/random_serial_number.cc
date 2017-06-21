#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

/**
 * O(N^3)
 *
 *
 * [remove print]
 *  $ time ./random_serial
 *  ./serial_number  1.25s user 0.02s system 99% cpu 1.269 total
 *  ./serial_number  1.28s user 0.00s system 99% cpu 1.281 total
 *  ./serial_number  0.97s user 0.00s system 99% cpu 0.974 total
 *
 */

class RandomSerialNumber {
    public:
        void operator()(std::vector<int> &serial, const int size);
};

int main(int argc, char *argv[]) {
    RandomSerialNumber random_serial_generator;
    std::vector<int> serial_number;
    random_serial_generator(serial_number, 8192);

    for (auto number : serial_number) {
        std::printf("%-6d", number);
    }

    return 0;
}

void RandomSerialNumber::operator()(std::vector<int> &serial, const int size) {
    srand((unsigned)time(NULL));
    bool re_rand;
    for (int i = 0, val; i < size; ++i) {
        do {
            re_rand = false;
            val = rand() % size + 1;

            for (int j = 0; j < i; ++j) {
                if (serial[j] == val) {
                    re_rand = true;
                    break;
                }
            }
        } while (re_rand);
        // assign
        serial.push_back(val);
    }
}
