#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef int DataType;
struct _stack_node_t {
    DataType data;
    struct _stack_node_t *next;
};
typedef struct _stack_node_t stack_node_t;
typedef stack_node_t *StackNode;

struct _stack_t {
    StackNode header;
    size_t stack_size;
};
typedef struct _stack_t stack_t;
typedef stack_t *Stack;


void make_empty(Stack *stack);
void stack_push(Stack stack, DataType data);
DataType stack_top(const Stack stack);
DataType stack_pop(Stack stack);
size_t stack_get_size(const Stack stack);
void stack_destroy(Stack *stack);


int main(void) {
    Stack stack;
    make_empty(&stack);
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

    return 0;
}


void make_empty(Stack *stack) {
    *stack = (Stack)(malloc(sizeof(stack_t)));
    (*stack)->header = NULL;
    (*stack)->stack_size = 0;
}


void stack_push(Stack stack, DataType data) {
    StackNode new_node = (StackNode)(malloc(sizeof(stack_node_t)));

    new_node->data = data;
    new_node->next = stack->header;

    stack->header = new_node;
    stack->stack_size += 1;
}

DataType stack_top(const Stack stack) {
    return stack->header->data;
}

DataType stack_pop(Stack stack) {
    StackNode header = stack->header;

    if (header == NULL) {
        fprintf(stderr, "cannot pop on empty stack");
        exit(1);
    }

    stack->header = header->next;
    stack->stack_size -= 1;

    return header->data;
}

size_t stack_get_size(const Stack stack) {
    return stack->stack_size;
}

void stack_destroy(Stack *stack) {
    while ((*stack)->stack_size) {
        stack_pop(*stack);
    }

    free(*stack);
    *stack = NULL;
}
