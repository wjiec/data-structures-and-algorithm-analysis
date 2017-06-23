#include <iostream>
#include <bitset>
#include <cmath>
#define SEQUENCE_SIZE 99999999

int main(int argc, char *argv[]) {
    auto sequence = new std::bitset<SEQUENCE_SIZE>;

    for (int i = 2, e = (int)std::sqrt(SEQUENCE_SIZE); i < e; ++i) {
        if (sequence->test((std::size_t)i)) {
            continue;
        }

        for (int j = i * 2; j < SEQUENCE_SIZE; j += i) {
            sequence->set((size_t)j);
        }
    }

    for (int i = 2; i < SEQUENCE_SIZE; ++i) {
        if (!sequence->test((std::size_t)i)) {
            // std::cout << " " << i << " ";
        }
    }

    return 0;
}
