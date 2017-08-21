#include "list_test.h"
#include "dlist_test.h"
#include "exercises.h"


int main(void) {
    list_test_suite();
    dlist_test_suite();

    /* Initializing Object */
    List list = create_list();
    DList dlist = create_dlist();

    list_insert(list, NULL, 9); dlist_insert(dlist, NULL, 9);
    list_insert(list, NULL, 7); dlist_insert(dlist, NULL, 7);
    list_insert(list, NULL, 6); dlist_insert(dlist, NULL, 6);
    list_insert(list, NULL, 5); dlist_insert(dlist, NULL, 5);
    list_insert(list, NULL, 3); dlist_insert(dlist, NULL, 3);
    list_insert(list, NULL, 2); dlist_insert(dlist, NULL, 2);
    list_insert(list, NULL, 1); dlist_insert(dlist, NULL, 1);

    printf("\n3.1 print out the elements of a singly/doubly linked list\n");
    print_list(list);
    print_dlist(dlist);

    return 0;
}
