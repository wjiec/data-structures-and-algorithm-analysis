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
    for (DListIter it = list->header->next; it != list->footer; dlist_next(list, &it)) {
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
    }

    list->list_size += 1;
    return node;
}

DListIter dlist_delete(DList list, DListIter iter) {
    DListIter new_iter;

    if (dlist_check_last(list, iter)) {
        new_iter = iter->prev->next = NULL;
    } else {
        new_iter = iter->prev->next = iter->next;
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
