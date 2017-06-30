#include <iostream>
#include <vector>
#include <cstdio>
#define NOT_FOUND -1


template <typename T>
class FindGtNd2 {
    public:
        T operator()(std::vector<T> &sequence);
};


int main(int argc, char *argv[]) {
    FindGtNd2<int> finder;

    std::vector<int> sequence_1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} :: %2d\n", finder(sequence_1));

    std::vector<int> sequence_2{0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    printf("{0, 1, 0, 1, 0, 1, 0, 1, 0, 1} :: %2d\n", finder(sequence_2));

    std::vector<int> sequence_3{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};
    printf("{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1} :: %2d\n", finder(sequence_3));

    std::vector<int> sequence_4{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1};
    printf("{0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1} :: %2d\n", finder(sequence_4));

    std::vector<int> sequence_5{1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};
    printf("{1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0} :: %2d\n", finder(sequence_5));

    std::vector<int> sequence_6{1, 0, 1, 0, 1};
    printf("{1, 0, 1, 0, 1} :: %2d\n", finder(sequence_6));

    std::vector<int> sequence_7{1, 1, 0, 1, 0};
    printf("{1, 1, 0, 1, 0} :: %2d\n", finder(sequence_7));
    return 0;
}


template <typename T>
T FindGtNd2<T>::operator()(std::vector<T> &sequence) {
    if (sequence.size() == 1) {
        return sequence[0];
    }

    T odd_num = (sequence.size() % 2) ? *(--sequence.end()) : NOT_FOUND;
    int odd_cnt = 1;

    std::vector<T> sub_sequence;
    for (auto it = sequence.cbegin(); it < sequence.cend(); it += 2) {
        if (*it == *(it + 1)) {
            sub_sequence.push_back(*it);

            if (odd_num != NOT_FOUND && *it == odd_num) {
                ++odd_cnt;
            }
        }
    }

    if (odd_num != NOT_FOUND && odd_cnt > (sub_sequence.size() + 1) / 2) {
        return odd_num;
    }

    if (sub_sequence.size() == 0) {
        if (odd_num != NOT_FOUND) {
            return odd_num;
        }
        return NOT_FOUND;
    }

    T result = operator()(sub_sequence);

    if (result == NOT_FOUND) {
        return NOT_FOUND;
    }

    auto result_cnt = 0;
    for (auto it = sequence.cbegin(); it != sequence.cend(); ++it) {
        if (*it == result) {
            ++result_cnt;
        }
    }
    if (result_cnt > sequence.size() / 2) {
        return result;
    }

    return NOT_FOUND;
}
