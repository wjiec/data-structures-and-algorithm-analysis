#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

char *infix_to_postfix_conv(const char *src) {
    Stack stack;
    make_empty(&stack);

    size_t di = 0;
    size_t src_len = strlen(src);
    char *dst = (char*)malloc(sizeof(char) * src_len + 1);
    memset(dst, 0, sizeof(char) * src_len + 1);

    for (size_t i = 0; i < src_len; ++i) {
        if (isalnum(src[i])) {
            dst[di++] = src[i];
            continue;
        }

        char top;
        switch (src[i]) {
            case '+':
            case '-':
                while (!stack_is_empty(stack) && (top = stack_top(stack))) {
                    if (top != '(') {
                        dst[di++] = stack_pop(stack);
                    } else {
                        break;
                    }
                }
                stack_push(stack, src[i]);
                break;
            case '*':
            case '/':
                while (!stack_is_empty(stack) && (top = stack_top(stack))) {
                    if (top == '*' || top == '/') {
                        dst[di++] = stack_pop(stack);
                    } else {
                        break;
                    }
                }
                stack_push(stack, src[i]);
                break;
            case '(':
                stack_push(stack, '(');
                break;
            case ')':
                while (!stack_is_empty(stack) && (top = stack_top(stack))) {
                    if (top != '(') {
                        dst[di++] = stack_pop(stack);
                    } else {
                        break;
                    }
                }
                stack_pop(stack); // pop '('
                break;
            case ' ': break;
            default:
                fprintf(stderr, "cannot resolve %c operator", src[i]);
                exit(1);
        }
    }

    while (!stack_is_empty(stack)) {
        if (stack_top(stack) == '(') {
            continue;
        }
        dst[di++] = stack_pop(stack);
    }

    stack_destroy(&stack);
    return dst;
}
