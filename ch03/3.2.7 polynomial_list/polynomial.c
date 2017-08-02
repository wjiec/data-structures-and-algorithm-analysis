#include <stdio.h>
#include <stdlib.h>


struct _polynomial_node_t {
    int coefficient;
    int exponent;
    struct _polynomial_node_t *next;
};
typedef struct _polynomial_node_t polynomial_node_t;
typedef polynomial_node_t *PolynomialNode;
typedef PolynomialNode Polynomial;

Polynomial make_polynomial(const int polynomial[][2], size_t length);
Polynomial add_polynomial(const Polynomial poly1, const Polynomial poly2);
Polynomial multi_polynomial(const Polynomial poly1, const Polynomial poly2);
void destroy_polynomial(Polynomial *poly);
void print_polynomial(const Polynomial poly);

int main(void) {
    const int poly1_info[][2] = {
        {5, 20}, {4, 17}, {1, 11}, {10, 9}, {14, 7}, {-8, 5}, {10, 0}
        // 5X^20 + 4X^17 + 1X^11 + 10X^9 + 14X^7 - 8X^5 + 10X^0
    };
    Polynomial poly1 = make_polynomial(poly1_info, 7);
    print_polynomial(poly1); puts("");

    const int poly2_info[][2] = {
        {7, 20}, {1, 19}, {9, 15}, {10, 9}, {-9, 6}, {-5, 2}, {10, 1}, {1, 0}
        // 7X^20 + 1X^19 + 9X^15 + 10X^9 - 9X^6 - 5X^2 + 10X^1 + 1X^0
    };
    Polynomial poly2 = make_polynomial(poly2_info, 8);
    print_polynomial(poly2); puts("");

    Polynomial add_result = add_polynomial(poly1, poly2);
    print_polynomial(add_result); puts("");

//    Polynomial multi_result = multi_polynomial(poly1, poly2);
//    print_polynomial(multi_result); puts("");

    destroy_polynomial(&poly1);
    destroy_polynomial(&poly2);
    destroy_polynomial(&add_result);
//    destroy_polynomial(&multi_result);

    return 0;
}

Polynomial make_polynomial(const int polynomial[][2], size_t length) {
    Polynomial poly = NULL;
    Polynomial *curr = &poly;

    for (size_t i = 0; i < length; ++i) {
        *curr = (PolynomialNode)(malloc(sizeof(polynomial_node_t)));

        (*curr)->coefficient = polynomial[i][0];
        (*curr)->exponent = polynomial[i][1];
        (*curr)->next = NULL;
        curr = &((*curr)->next);
    }

    return poly;
}

Polynomial add_polynomial(const Polynomial poly1, const Polynomial poly2) {
    //-------------------------------------------------------------------
    PolynomialNode poly1_ptr = poly1;
    PolynomialNode poly2_ptr = poly2;

    Polynomial result;
    Polynomial *curr_ret = &result;

    int coefficient;
    int exponent;

    while (1) {
        if (poly1_ptr == NULL || poly2_ptr == NULL) {
            break;
        }

        if (poly1_ptr->exponent > poly2_ptr->exponent) {
            coefficient = poly1_ptr->coefficient;
            exponent = poly1_ptr->exponent;

            poly1_ptr = poly1_ptr->next;
        } else if (poly1_ptr->exponent < poly2_ptr->exponent) {
            coefficient = poly2_ptr->coefficient;
            exponent = poly2_ptr->exponent;

            poly2_ptr = poly2_ptr->next;
        } else {
            coefficient = poly1_ptr->coefficient + poly2_ptr->coefficient;
            exponent = poly1_ptr->exponent;

            poly1_ptr = poly1_ptr->next;
            poly2_ptr = poly2_ptr->next;
        }

        *curr_ret = (PolynomialNode)(malloc(sizeof(polynomial_node_t)));
        (*curr_ret)->coefficient = coefficient;
        (*curr_ret)->exponent = exponent;
        (*curr_ret)->next = NULL;

        curr_ret = &((*curr_ret)->next);
    }

    PolynomialNode last_nodes = NULL;

    if (poly1_ptr == NULL) {
        last_nodes = poly2_ptr;
    }

    if (poly2_ptr == NULL) {
        last_nodes = poly1_ptr;
    }

    for (; last_nodes != NULL;  last_nodes = last_nodes->next) {
        *curr_ret = (PolynomialNode)(malloc(sizeof(polynomial_node_t)));
        (*curr_ret)->coefficient = last_nodes->coefficient;
        (*curr_ret)->exponent = last_nodes->exponent;
        (*curr_ret)->next = NULL;

        curr_ret = &((*curr_ret)->next);
    }

    return result;
}

Polynomial multi_polynomial(const Polynomial poly1, const Polynomial poly2) {

}

void destroy_polynomial(Polynomial *poly) {
    PolynomialNode next;
    for (PolynomialNode curr = *poly; curr != NULL; curr = next) {
        next = curr->next;
        free(curr);
    }
}

void print_polynomial(const Polynomial poly) {
    for (PolynomialNode curr = poly; curr != NULL; curr = curr->next) {
        printf("%dX^%d", curr->coefficient, curr->exponent);
        if (curr->next != NULL) {
            printf(" + ");
        }
    }
}
