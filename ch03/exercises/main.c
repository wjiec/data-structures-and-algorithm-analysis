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


    List index_list = create_list();
    DList index_dlist = create_dlist();

    list_insert(index_list, list_footer(index_list), 1);
    list_insert(index_list, list_footer(index_list), 3);
    list_insert(index_list, list_footer(index_list), 5);

    dlist_insert(index_dlist, dlist_footer(index_dlist), 1);
    dlist_insert(index_dlist, dlist_footer(index_dlist), 3);
    dlist_insert(index_dlist, dlist_footer(index_dlist), 5);

    printf("\n3.2 Print the elements in L that are in positions specified by P.\n");
    print_list(index_list);
    print_dlist(index_dlist);
    print_list_by_index(list, index_list);
    print_dlist_by_index(dlist, index_dlist);

    return 0;
}
