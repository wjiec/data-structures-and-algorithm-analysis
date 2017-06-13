#include <iostream>
#include <vector>


using namespace std;


template <typename T>
class MaxSubSequenceSum {
public:
    MaxSubSequenceSum(vector<T> &sequence);

public:
    typedef struct max_sum_result {
        T sum;
        int left_index;
        int right_index;
    } result_type;
    // method
    void divide_and_conquer();

private:
    result_type divide_and_conquer(int left_index, int right_index);

public:
    result_type sum;

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
        divide.divide_and_conquer();
        // output
        cout << "Max sub sequence sum: " << divide.sum.sum << "(" << divide.sum.left_index << ", " << divide.sum.right_index << ")" << endl;
    }

    return 0;
}


template <typename T>
MaxSubSequenceSum<T>::MaxSubSequenceSum(vector<T> &sequence) :
        sequence(sequence), sum(result_type {sequence[0], 0, 0}) {
    // cannot do anything
}

template <typename T>
void MaxSubSequenceSum<T>::divide_and_conquer() {
    sum = divide_and_conquer(0, sequence.size() - 1);
}

template <typename T>
typename MaxSubSequenceSum<T>::result_type MaxSubSequenceSum<T>::divide_and_conquer(int left_index, int right_index) {
// ^^^^^ here is very important, tells the compiler that `result_type` is type name not value !!!
    // base case
    if (left_index == right_index) {
        return result_type{sequence[left_index], left_index, right_index};
    }

    // calc left/right sum
    int center_index = (left_index + right_index) / 2;
    result_type left_max_sum = divide_and_conquer(left_index, center_index);
    result_type right_max_sum = divide_and_conquer(center_index + 1, right_index);

    // left border sum
    result_type left_border_max_sum{sequence[center_index], center_index, center_index};
    T left_border_sum = 0;
    for (int i = center_index; i >= left_index; --i) {
        left_border_sum += sequence[i];
        if (left_border_sum > left_border_max_sum.sum) {
            left_border_max_sum.sum = left_border_sum;
            left_border_max_sum.left_index = i;
        }
    }

    // right border sum
    result_type right_border_max_sum{sequence[center_index + 1], center_index + 1, center_index + 1};
    T right_border_sum = 0;
    for (int i = center_index + 1; i <= right_index; ++i) {
        right_border_sum += sequence[i];
        if (right_border_sum > right_border_max_sum.sum) {
            right_border_max_sum.sum = right_border_sum;
            right_border_max_sum.right_index = i;
        }
    }

    // select max sum and return
    T left_and_right_border_sum = left_border_max_sum.sum + right_border_max_sum.sum;
    if (left_and_right_border_sum > left_max_sum.sum && left_and_right_border_sum > right_max_sum.sum) {
        return result_type{left_and_right_border_sum, left_border_max_sum.left_index, right_border_max_sum.right_index};
    } else if (left_max_sum.sum > left_and_right_border_sum && left_max_sum.sum > right_max_sum.sum) {
        return left_max_sum;
    } else {
        return right_max_sum;
    }
}
