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
