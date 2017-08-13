#include <stdio.h>
#include <string.h>
#include "stack.h"


extern bool balancing_symbols(const char *string) {
    if (string == NULL || strlen(string) == 0) {
        return true;
    }

    Stack stack;
    make_empty(&stack);

    size_t string_length = strlen(string);
    for (size_t i = 0; i < string_length; ++i) {
        if (string[i] == '{' || string[i] == '[' || string[i] == '(') {
            stack_push(stack, string[i]);
        } else if (string[i] == '}' || string[i] == ']' || string[i] == ')') {
            if (stack_is_empty(stack)) {
                return false;
            }

            char except_symbol;
            switch (stack_pop(stack)) {
                case '{': except_symbol = '}'; break;
                case '[': except_symbol = ']'; break;
                case '(': except_symbol = ')'; break;
                default: return false;
            }
            if (string[i] != except_symbol) {
                return false;
            }
        }
    }

    stack_destroy(&stack);
    return true;
}
