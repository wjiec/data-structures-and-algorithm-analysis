#include <stdio.h>
#include <stdlib.h>
#include "list.h"


/* Definition for ListNode */
struct _list_node_t {
    DataType data;
    ListIter next;
};

/* Definition for List */
struct _list_t {
    ListIter header;
    ListIter footer;
    ListSize list_size;
};


/* Static methods */
static ListIter list_find_prev_iter(const List list, const ListIter iter);


/* Definition for list methods */
List create_list(void) {
    List list = (List)(malloc(sizeof(list_t)));

    list->header = (ListNode)(malloc(sizeof(list_node_t)));
    list->header->next = NULL; // previous iterator of header
    list->footer = NULL;
    list->list_size = 0;

    return list;
}

bool list_is_empty(const List list) {
    return list->list_size == 0;
}

bool list_check_last(const List list, const ListIter iter) {
    return list->footer == iter;
}

ListIter list_find(const List list, const DataType data) {
    ListIter it = list_find_previous(list, data);
    list_next(list, &it);

    return it;
}

ListIter list_find_previous(const List list, const DataType data) {
    if (list_is_empty(list)) {
        return NULL;
    }

    for (ListIter it = list->header; it->next && it != list->footer; list_next(list, &it)) {
        if (it->next->data == data) {
            return it;
        }
    }
    return NULL;
}

/* If iter is NULL, than append to header of List */
ListIter list_insert(List list, ListIter iter, DataType data) {
    ListNode node = (ListNode)(malloc(sizeof(list_node_t)));
    node->data = data;

    if (iter == NULL) {
        // append to header of list
        if (list->header->next == NULL) {
            list->footer = node;
        }

        node->next = list->header->next;
        list->header->next = node;
    } else {
        node->next = iter->next;
        iter->next = node;
    }

    list->list_size += 1;
    return node;
}

ListIter list_delete(List list, ListIter iter) {
    ListIter prev_iter = list_find_prev_iter(list, iter);
    if (prev_iter == NULL) {
        return NULL;
    }

    if (iter == list->footer) {
        // update footer node
        list->footer = prev_iter;
    }

    prev_iter->next = iter->next;
    free(iter);

    list->list_size -= 1;
    return prev_iter->next;
}

ListIter list_header(const List list) {
    return list->header->next;
}

ListIter list_footer(const List list) {
    return list->footer;
}

void list_next(List list, ListIter *iter) {
    if (!list_is_empty(list) && *iter != NULL) {
        *iter = (*iter)->next;
    }
}

void list_prev(List list, ListIter *iter) {
    *iter = list_find_prev_iter(list, *iter);
}

DataType list_retrieve(const ListIter iter) {
    return iter->data;
}

ListSize list_get_size(const List list) {
    return list->list_size;
}

void list_destroy(List *list) {
    while (!list_is_empty(*list)) {
        list_delete(*list, list_header(*list));
    }

    free(*list);
    *list = NULL;
}

static ListIter list_find_prev_iter(const List list, const ListIter iter) {
    for (ListIter it = list->header; it->next && it != list->footer; list_next(list, &it)) {
        if (it->next == iter) {
            return it;
        }
    }
    return NULL;
}
