#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int DataType;
struct _stack_t {
    DataType *array;
    size_t capacity;
    int stack_index;
};
typedef struct _stack_t stack_t;
typedef stack_t *Stack;


void make_empty(Stack *stack, size_t max_stack_size);
bool stack_is_empty(const Stack stack);
bool stack_is_full(const Stack stack);
void stack_push(Stack stack, DataType data);
DataType stack_top(const Stack stack);
DataType stack_pop(Stack stack);
size_t stack_get_size(const Stack stack);
void stack_destroy(Stack *stack);


int main(void) {
    Stack stack;
    make_empty(&stack, 16);
    assert(stack_get_size(stack) == 0);

    stack_push(stack, 1);
    assert(stack_top(stack) == 1);
    assert(stack_get_size(stack) == 1);

    stack_push(stack, 2);
    assert(stack_top(stack) == 2);

    stack_push(stack, 3);
    assert(stack_top(stack) == 3);
    assert(stack_get_size(stack) == 3);

    assert(stack_pop(stack) == 3);
    assert(stack_top(stack) == 2);
    assert(stack_get_size(stack) == 2);

    stack_destroy(&stack);
    assert(stack == NULL);

    make_empty(&stack, 2);
    stack_push(stack, 1);
    stack_push(stack, 2);
    assert(stack_get_size(stack) == 2);
    assert(stack_is_full(stack) == true);

    stack_destroy(&stack);
    assert(stack == NULL);

    return 0;
}


void make_empty(Stack *stack, size_t max_stack_size) {
    if (max_stack_size < 1) {
        fprintf(stderr, "stack size too small\n");
        exit(1);
    }

    (*stack) = (Stack)(malloc(sizeof(stack_t)));

    (*stack)->stack_index = -1;
    (*stack)->capacity = max_stack_size;
    (*stack)->array = (DataType*)(malloc(sizeof(DataType) * max_stack_size));
    if ((*stack)->array == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
}

bool stack_is_empty(const Stack stack) {
    return stack->stack_index == -1;
}

bool stack_is_full(const Stack stack) {
    return stack->stack_index + 1 == stack->capacity;
}

void stack_push(Stack stack, DataType data) {
    if (stack_is_full(stack)) {
        fprintf(stderr, "stack is full");
        exit(1);
    }
    stack->array[++stack->stack_index] = data;
}

DataType stack_top(const Stack stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "stack is empty");
        exit(1);
    }
    return stack->array[stack->stack_index];
}

DataType stack_pop(Stack stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "stack is empty");
        exit(1);
    }
    return stack->array[stack->stack_index--];
}

size_t stack_get_size(const Stack stack) {
    return (size_t)(stack->stack_index + 1);
}

void stack_destroy(Stack *stack) {
    while (stack_is_empty(*stack)) {
        stack_pop(*stack);
    }
    free(*stack);
    *stack = NULL;
}
