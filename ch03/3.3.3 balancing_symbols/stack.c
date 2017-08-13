#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

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


extern void make_empty(Stack *stack) {
    *stack = (Stack)(malloc(sizeof(stack_t)));
    (*stack)->header = NULL;
    (*stack)->stack_size = 0;
}

extern bool stack_is_empty(const Stack stack) {
    return stack->header == NULL;
}

extern void stack_push(Stack stack, DataType data) {
    StackNode new_node = (StackNode)(malloc(sizeof(stack_node_t)));

    new_node->data = data;
    new_node->next = stack->header;

    stack->header = new_node;
    stack->stack_size += 1;
}

extern DataType stack_pop(Stack stack) {
    StackNode header = stack->header;

    if (header == NULL) {
        fprintf(stderr, "cannot pop on empty stack");
        exit(1);
    }

    stack->header = header->next;
    stack->stack_size -= 1;

    return header->data;
}

extern void stack_destroy(Stack *stack) {
    while ((*stack)->stack_size) {
        stack_pop(*stack);
    }

    free(*stack);
    *stack = NULL;
}

