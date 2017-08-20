#include <stdio.h>
#include <assert.h>
#include "list.h"


/* Suite of list */
void list_test_suite() {
    printf("[ListTest] ListTest Suite Start ...\n");

    List list = create_list();
    assert(list_is_empty(list));

    ListIter header_iter = list_header(list);
    assert(header_iter == NULL);
    assert(list_find(list, 9) == NULL);

    list_insert(list, header_iter, 1); // 1
    assert(list_get_size(list) == 1);
    assert(list_retrieve(list_header(list)) == 1);

    list_insert(list, NULL, 0); // 0 1
    assert(list_get_size(list) == 2);
    assert(list_retrieve(list_header(list)) == 0);

    ListIter find_1 = list_find(list, 1);
    assert(list_retrieve(find_1) == 1);

    list_delete(list, find_1);
    assert(list_get_size(list) == 1);

    header_iter = list_header(list);
    list_next(list, &header_iter);
    assert(header_iter == NULL);

    ListIter footer_iter = list_footer(list);
    assert(list_check_last(list, footer_iter));

    list_insert(list, NULL, -1);
    ListIter prev_0 = list_find_previous(list, 0);
    assert(list_retrieve(prev_0) == -1);

    ListIter find_0 = list_find(list, 0);
    list_prev(list, &find_0);
    assert(find_0 == prev_0);

    list_destroy(&list);
    assert(list == NULL);

    printf("[ListTest] ListTest Suite Success\n");
}
