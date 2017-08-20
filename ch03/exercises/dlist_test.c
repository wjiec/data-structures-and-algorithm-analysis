#include <stdio.h>
#include <assert.h>
#include "dlist.h"
#include "dlist_test.h"

void dlist_test_suite() {
    printf("[DListTest] DListTest Suite Start ...\n");

    DList list = create_dlist();
    assert(dlist_is_empty(list));

    DListIter header_iter = dlist_header(list);
    assert(header_iter == NULL);
    assert(dlist_find(list, 9) == NULL);

    dlist_insert(list, header_iter, 1);
    assert(dlist_get_size(list) == 1);
    assert(dlist_retrieve(dlist_header(list)) == 1);

    dlist_insert(list, NULL, 0);
    assert(dlist_get_size(list) == 2);
    assert(dlist_retrieve(dlist_header(list)) == 0);

    DListIter find_1 = dlist_find(list, 1);
    assert(dlist_retrieve(find_1) == 1);

    dlist_delete(list, find_1);
    assert(dlist_get_size(list) == 1);

    header_iter = dlist_header(list);
    dlist_next(list, &header_iter);
    assert(header_iter == NULL);

    DListIter footer_iter = dlist_footer(list);
    assert(dlist_check_last(list, footer_iter));

    dlist_insert(list, NULL, -1);
    DListIter prev_0 = dlist_find_previous(list, 0);
    assert(dlist_retrieve(prev_0) == -1);

    DListIter find_0 = dlist_find(list, 0);
    dlist_prev(list, &find_0);
    assert(find_0 == prev_0);

    dlist_destroy(&list);
    assert(list == NULL);

    printf("[ListTest] ListTest Suite Success\n");
}
