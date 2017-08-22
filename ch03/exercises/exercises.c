#include "list.h"
#include "dlist.h"
#include "exercises.h"


/* print out the elements of a singly/doubly linked list */
void print_list(const List list) {
    printf("Singly-Link List: ");
    ListIter it = list_header(list);
    for (; it != NULL; list_next(list, &it)) {
        printf("%4d", list_retrieve(it));
    }
    printf("\n");
}

void print_dlist(const DList dlist) {
    printf("Doubly-Link List: ");
    DListIter it = dlist_header(dlist);
    for (; it != NULL; dlist_next(dlist, &it)) {
        printf("%4d", dlist_retrieve(it));
    }
    printf("\n");
}

void print_list_by_index(const List list, const List index) {
    size_t idx = 0;

    printf("Singly-Link List By Index: ");
    ListIter l_it = list_header(list);
    for (ListIter i_it = list_header(index); i_it && l_it; ) {
        if (list_retrieve(i_it) == idx + 1) {
            printf("%4d", list_retrieve(l_it));
            list_next(index, &i_it);
        }
        list_next(list, &l_it);
        idx += 1;
    }
    printf("\n");
}

void print_dlist_by_index(const DList list, const DList index) {
    size_t idx = 0;

    printf("Doubly-Link List By Index: ");
    DListIter l_it = dlist_header(list);
    for (DListIter i_it = dlist_header(index); i_it && l_it; ) {
        if (dlist_retrieve(i_it) == idx + 1) {
            printf("%4d", dlist_retrieve(l_it));
            dlist_next(index, &i_it);
        }
        dlist_next(list, &l_it);
        idx += 1;
    }
    printf("\n");
}
