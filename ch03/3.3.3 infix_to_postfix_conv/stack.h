//
// Created by ShadowMan on 2017/8/13.
//

#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>

typedef char DataType;
typedef struct _stack_t stack_t;
typedef stack_t *Stack;

void make_empty(Stack *stack);
bool stack_is_empty(const Stack stack);
void stack_push(Stack stack, DataType data);
DataType stack_top(const Stack stack);
DataType stack_pop(Stack stack);
void stack_destroy(Stack *stack);

#endif // _STACK_H
