#ifndef _EXERCISES_H
#define _EXERCISES_H

#include "list.h"
#include "dlist.h"

/* print out the elements of a singly/doubly linked list */
void print_list(const List list);
void print_dlist(const DList dlist);

/* Print the elements in L that are in positions specified by P */
void print_list_by_index(const List list, const List index);
void print_dlist_by_index(const DList list, const DList index);

#endif // _EXERCISES_H
