#include <iostream>
#include <vector>


using namespace std;


template <typename T>
class MaxSubSequenceSum {
public:
    MaxSubSequenceSum(vector<T> &sequence);

public:
    void brute_force();

public:
    T sum;
    size_t left_index;
    size_t right_index;

private:
    vector<T> &sequence;
};


int main(int argc, char *argv[]) {
    vector<vector<int>> sequences{
            { 4, -3, 5, -2, -1, 2, 6, -2 },
            { 1, 2, 3, 4, -4, -3, -2, -1 },
            { 1, -1, 2, -2, 3, -3, 4, -4 },
            { 1, -1, 1, -1, 1, -1, 1, -1 },
            { 1, 2, 3, 4, 5, 6, 7, -1000 },
            { -100, 1, 2, 3, 4, 5, -9, 1 }
    };

    for (auto &sequence : sequences) {
        auto bf = MaxSubSequenceSum<int>(sequence);
        // brute force method
        bf.brute_force();
        // output
        cout << "Max sub sequence sum: " << bf.sum << "(" << bf.left_index << ", " << bf.right_index << ")" << endl;
    }

    return 0;
}


template <typename T>
MaxSubSequenceSum<T>::MaxSubSequenceSum(vector<T> &sequence) :
        sequence(sequence), left_index(0), right_index(0), sum(sequence[0]) {
    // cannot do anything
}

template <typename T>
void MaxSubSequenceSum<T>::brute_force() {
    auto end = sequence.cend();
    // start position
    for (auto i = sequence.cbegin(); i < end; ++i) {
        // end position
        for (auto j = i; j < end; ++j) {
            T current_sum = 0;
            // calc current sum
            for (auto k = i; k < j; ++k) {
                current_sum += *k;
            }
            // current sum bigger than max sum
            if (current_sum > sum) {
                sum = current_sum;
                left_index = i - sequence.cbegin();
                right_index = j - sequence.cbegin();
            }
        }
    }
}
