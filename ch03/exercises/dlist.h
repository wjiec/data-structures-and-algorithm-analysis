#ifndef _DLIST_H
#define _DLIST_H

#include <stdio.h>
#include <stdbool.h>


/* Definition for Data */
typedef int DDataType;

/* Declaration for ListNode */
typedef struct _dlist_node_t dlist_node_t;
typedef dlist_node_t *DListNode;
typedef DListNode DListIter;

/* Declaration for list */
typedef struct _dlist_t dlist_t;
typedef dlist_t *DList;

/* Definition for ListSize */
typedef size_t DListSize;

/* Methods for list */
DList create_dlist(void);
bool dlist_is_empty(const DList list);
bool dlist_check_last(const DList list, const DListIter iter);
DListIter dlist_find(const DList list, const DDataType data);
DListIter dlist_find_previous(const DList list, const DDataType data);
DListIter dlist_insert(DList list, DListIter it, DDataType data);
DListIter dlist_delete(DList list, DListIter iter);
DListIter dlist_header(const DList list);
DListIter dlist_footer(const DList list);
void dlist_next(DList list, DListIter *iter);
void dlist_prev(DList list, DListIter *iter);
DDataType dlist_retrieve(const DListIter iter);
DListSize dlist_get_size(const DList list);
void dlist_destroy(DList *list);

#endif // _DLIST_H
