#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"


/* Definition with doubly-link list node */
struct _dlist_node_t {
    DDataType data;
    DListIter prev;
    DListIter next;
};

/* Definition with doubly-link list */
struct _dlist_t {
    DListIter header;
    DListIter footer;
    DListSize list_size;
};

DList create_dlist(void) {
    DList list = (DList)(malloc(sizeof(dlist_t)));

    list->header = (DListNode)(malloc(sizeof(dlist_node_t)));
    list->header->prev = NULL;
    list->header->next = NULL;
    list->footer = NULL;
    list->list_size = 0;

    return list;
}

bool dlist_is_empty(const DList list) {
    return list->list_size == 0;
}

bool dlist_check_last(const DList list, const DListIter iter) {
    return list->footer == iter;
}

DListIter dlist_find(const DList list, const DDataType data) {
    for (DListIter it = list->header->next; it != NULL; dlist_next(list, &it)) {
        if (it->data == data) {
            return it;
        }
    }
    return NULL;
}

DListIter dlist_find_previous(const DList list, const DDataType data) {
    DListIter rst = dlist_find(list, data);
    return rst ? rst->prev : rst;
}

DListIter dlist_insert(DList list, DListIter it, DDataType data) {
    DListNode node = (malloc(sizeof(dlist_node_t)));
    node->data = data;

    if (it == NULL) {
        node->prev = list->header;
        // insert into list header
        if (list->header->next == NULL) {
            // first element
            node->next = NULL;
            list->footer = node;
        } else {
            // non first element
            node->next = list->header->next;
            list->header->next->prev = node;
        }
        list->header->next = node;
    } else {
        node->prev = it;
        node->next = it->next;
        it->next = node;

        if (node->next == NULL) {
            list->footer = node;
        }
    }

    list->list_size += 1;
    return node;
}

DListIter dlist_delete(DList list, DListIter iter) {
    DListIter new_iter;

    if (dlist_check_last(list, iter)) {
        list->footer = iter->prev;
        new_iter = iter->prev->next = NULL;
    } else {
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
        new_iter = iter->next;
    }

    free(iter);
    list->list_size -= 1;
    return new_iter;
}

DListIter dlist_header(const DList list) {
    return list->header->next;
}

DListIter dlist_footer(const DList list) {
    return list->footer;
}

void dlist_next(DList list, DListIter *iter) {
    if (list->footer == *iter) {
        *iter = NULL; // disable list unused warning
    } else {
        *iter = (*iter)->next;
    }
}

void dlist_prev(DList list, DListIter *iter) {
    if (list->header == *iter) {
        *iter = NULL;
    } else {
        *iter = (*iter)->prev;
    }
}

DDataType dlist_retrieve(const DListIter iter) {
    return iter->data;
}

DListSize dlist_get_size(const DList list) {
    return list->list_size;
}

void dlist_destroy(DList *list) {
    while (!dlist_is_empty(*list)) {
        dlist_delete(*list, dlist_header(*list));
    }

    free(*list);
    *list = NULL;
}

/* 3.3 Swap pointer */
void dlist_swap_diterator(DList list, DListIter it1, DListIter it2) {
    DListIter it1_prev = it1->prev;
    DListIter it1_next = it1->next;

    DListIter it2_prev = it2->prev;
    DListIter it2_next = it2->next;

    it1->prev = it2_prev;
    it1->next = it2_next;

    it2->prev = it1_prev;
    it2->next = it1_next;

    it1_prev->next = it2;
    it1_next->prev = it2;

    it2_prev->next = it1;
    it2_next->prev = it1;
}
