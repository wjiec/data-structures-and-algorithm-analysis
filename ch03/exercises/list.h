#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdbool.h>


/* Definition for Data */
typedef int DataType;

/* Declaration for ListNode */
typedef struct _list_node_t list_node_t;
typedef list_node_t *ListNode;
typedef ListNode ListIter;

/* Declaration for list */
typedef struct _list_t list_t;
typedef list_t *List;

/* Definition for ListSize */
typedef size_t ListSize;

/* Methods for list */
List create_list(void);
bool list_is_empty(const List list);
bool list_check_last(const List list, const ListIter iter);
ListIter list_find(const List list, const DataType data);
ListIter list_find_previous(const List list, const DataType data);
ListIter list_insert(List list, ListIter it, DataType data);
ListIter list_delete(List list, ListIter iter);
ListIter list_header(const List list);
ListIter list_footer(const List list);
void list_next(List list, ListIter *iter);
void list_prev(List list, ListIter *iter);
DataType list_retrieve(const ListIter iter);
ListSize list_get_size(const List list);
void list_destroy(List *list);

/* 3.3 Swap Pointer */
void list_swap_iterator(List list, ListIter it1, ListIter it2);

#endif // _LIST_H
