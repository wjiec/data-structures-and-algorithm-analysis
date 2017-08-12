#include <iostream>
#include <algorithm>


template <typename T>
class Stack {
    public:
        Stack(size_t max_stack_size);
        Stack(Stack &stack);
        Stack(Stack &&stack);
        ~Stack();

    public:
        bool is_empty();
        bool is_full();
        size_t get_size();
        size_t get_capacity();
        void push(const T &data);
        T pop();
        T top();

    private:
        T *_array;
        size_t _capacity;
        int _stack_index;
};


int main(void) {
    auto int_stack = new Stack<int>(2);

    std::cout << "Stack size => " << int_stack->get_size() << std::endl;
    std::cout << "Stack capacity => " << int_stack->get_capacity() << std::endl;

    int_stack->push(0xff);
    std::cout <<  std::endl
              << "Stack size => " << int_stack->get_size() << std::endl;
    std::cout << "Stack top => " << int_stack->top() << std::endl;

    int_stack->push(0xee);
    std::cout <<  std::endl
              << "Stack size => " << int_stack->get_size() << std::endl;
    std::cout << "Stack top => " << int_stack->top() << std::endl;

    std::cout <<  std::endl
              << "Stack is full => " << int_stack->is_full() << std::endl;

    auto data = int_stack->pop();
    std::cout << "Pop data => " << data << std::endl
              << "Stack top is => " << int_stack->top() << std::endl
              << "Stack size => " << int_stack->get_size() << std::endl;


    auto copy_stack = new Stack<int>(*int_stack);
    std::cout << std::endl
              << "Copy stack size => " << copy_stack->get_size() << std::endl
              << "Copy stack capacity => " << copy_stack->get_capacity()
              << std::endl;

    copy_stack->push(0xaa);
    std::cout << std::endl
              << "Copy stack size => " << copy_stack->get_size() << std::endl
              << "Origin stack size => " << int_stack->get_size() << std::endl;

    auto move_stack = new Stack<int>(std::move(*copy_stack));
    std::cout << std::endl
              << "Move stack size => " << move_stack->get_size() << std::endl
              << "Move stack capacity => " << move_stack->get_capacity()
              << std::endl
              << "Copy stack size => " << copy_stack->get_size() << std::endl
              << "Copy stack capacity => " << copy_stack->get_capacity()
              << std::endl;

    delete int_stack;
    delete copy_stack;
    delete move_stack;

    return 0;
}


template <typename T>
Stack<T>::Stack(size_t max_stack_size) :
        _capacity(max_stack_size), _stack_index(-1) {
    //-------------------------------------------
    if (_capacity < 1) {
        throw new std::runtime_error("stack size too small");
    }

    _array = new T[_capacity];
}

template <typename T>
Stack<T>::Stack(Stack &stack) :
        _capacity(stack._capacity), _stack_index(stack._stack_index) {
    //------------------------------------------------------------

    _array = new T[_capacity];
    std::copy_n(stack._array, stack._stack_index + 1, _array);
}

template <typename T>
Stack<T>::Stack(Stack &&stack) :
        _capacity(stack._capacity), _stack_index(stack._stack_index),
        _array(stack._array) {
    //-----------------------------------------------------------
    stack._array = nullptr;
    stack._stack_index = -1;
    stack._capacity = 0;
}

template <typename T>
Stack<T>::~Stack() {
    delete []_array;
    _capacity = 0;
    _stack_index = -1;
}

template <typename T>
bool Stack<T>::is_empty() {
    return _stack_index + 1 == 0;
}

template <typename T>
size_t Stack<T>::get_capacity() {
    return _capacity;
}

template <typename T>
size_t Stack<T>::get_size() {
    return static_cast<size_t>(_stack_index + 1);
}

template <typename T>
bool Stack<T>::is_full() {
    return _stack_index + 1 == _capacity;
}

template <typename T>
void Stack<T>::push(const T &data) {
    if (is_full()) {
        throw new std::runtime_error("stack is full");
    }
    _array[++_stack_index] = data;
}

template <typename T>
T Stack<T>::top() {
    if (is_empty()) {
        throw new std::runtime_error("stack is empty");
    }
    return _array[_stack_index];
}

template <typename T>
T Stack<T>::pop() {
    if (is_empty()) {
        throw new std::runtime_error("stack is empty");
    }
    return _array[_stack_index--];
}
