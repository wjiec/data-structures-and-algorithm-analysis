#include <iostream>
#include <vector>


using namespace std;


template <typename T>
class MaxSubSequenceSum {
public:
    MaxSubSequenceSum(vector<T> &sequence);

public:
    // method
    void calc();

public:
    T sum;

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
        auto divide = MaxSubSequenceSum<int>(sequence);
        // brute force method
        divide.calc();
        // output
        cout << "Max sub sequence sum: " << divide.sum << endl;
    }

    return 0;
}


template <typename T>
MaxSubSequenceSum<T>::MaxSubSequenceSum(vector<T> &sequence) :
        sequence(sequence), sum(sequence[0]) {
    // cannot do anything
}

template <typename T>
void MaxSubSequenceSum<T>::calc() {
    for (T curr_sum = 0, i = 0; i < sequence.size(); ++i) {
        curr_sum += sequence[i];

        if (curr_sum > sum) {
            sum = curr_sum;
        } else if (curr_sum < 0) {
            curr_sum = 0;
        }
    }
}
