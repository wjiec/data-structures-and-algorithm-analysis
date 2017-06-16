#include <iostream>
#include <vector>
#define NOT_FOUND -1

using namespace std;

template <typename T>
class BinarySearch {
    public:
        BinarySearch(const vector<T> &sequence);

    public:
        typedef int position;

    public:
        position search(const T &element);

    private:
        vector<T> _sequence;
};


int main(int argc, char *argv[]) {
    vector<int> sequence{ 0, 1, 3, 5, 6, 7, 8, 9 };
    BinarySearch<int> searcher(sequence);

    cout << "Binary Search: " << searcher.search(2) << endl;
    cout << "Binary Search: " << searcher.search(5) << endl;
    cout << "Binary Search: " << searcher.search(9) << endl;
    return 0;
}


template <typename T>
BinarySearch<T>::BinarySearch(const vector<T> &sequence)
        : _sequence(sequence) {
    // constructor cannot do anything
}

template <typename T>
typename BinarySearch<T>::position BinarySearch<T>::search(const T &element) {
    position start = 0, end = _sequence.size() - 1;
    position center;

    while (start <= end) {
        center = (start + end) / 2;

        if (element > _sequence[center]) {
            start = center + 1;
        } else if (element < _sequence[center]) {
            end = center - 1;
        } else {
            return center;
        }
    }
    return NOT_FOUND;
}
