#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DataType;

struct _list_node_t {
    DataType data;
    struct _list_node_t *prev;
    struct _list_node_t *next;
};
typedef struct _list_node_t list_node_t;
typedef list_node_t *ListNode;

struct _list_t {
    size_t size;
    ListNode header;
    ListNode footer;
};
typedef struct _list_t list_t;
typedef list_t *List;

typedef size_t Position;


/* Methods for doubly linked list */
void make_empty(List *list);
void insert(List list, Position pos, DataType data);


static ListNode new_list_node(DataType data, ListNode prev, ListNode next);


int main(void) {
    List list;

    make_empty(&list);
    insert(list, 0, 1);
    insert(list, 0, 2);
    insert(list, 0, 3);
}

/* Method Definition */
void make_empty(List *list) {
    *list = (List)malloc(sizeof(list_t));

    (*list)->size = 0;
    (*list)->header = NULL;
    (*list)->footer = NULL;
}

void insert(List list, Position pos, DataType data) {
    if (list->header == NULL) {
        // first data
        list->size = 1;
        list->header = new_list_node(data, NULL, NULL);
        list->footer = list->header;
    } else {
        
    }
}

static ListNode new_list_node(DataType data, ListNode prev, ListNode next) {
    ListNode node = (ListNode)malloc(sizeof(list_node_t));

    node->data = data;
    node->prev = prev;
    node->next = next;

    return node;
}
