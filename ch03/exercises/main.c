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

    list_destroy(&index_list);
    dlist_destroy(&index_dlist);


    ListIter it1 = list_find(list, 7); DListIter dit1 = dlist_find(dlist, 7);
    ListIter it2 = list_find(list, 2); DListIter dit2 = dlist_find(dlist, 2);

    list_swap_iterator(list, it1, it2);
    dlist_swap_diterator(dlist, dit1, dit2);

    printf("\n3.3 swap two adjacent elements by adjusting only the pointers\n");
    print_list(list);
    print_dlist(dlist);

    return 0;
}
