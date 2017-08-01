#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

struct _list_node_t {
    DataType data;
    struct _list_node_t *prev;
    struct _list_node_t *next;
};
typedef struct _list_node_t list_node_t;
typedef list_node_t *ListNode;

struct _list_t {
    ListNode header;
    ListNode footer;
};
typedef struct _list_t list_t;
typedef list_t *List;

typedef ListNode Position;


/* Methods for doubly linked list */
void make_empty(List *list);
Position insert(List list, Position pos, DataType data);
Position header(const List list);
Position footer(const List list);
Position find(const List list, const DataType data);
Position next(Position pos);
DataType retrieve(Position pos);
Position delete(Position pos);
void destroy_list(List *list);
void print_list(const List list);

static ListNode new_list_node(DataType data, ListNode prev, ListNode next);


int main(void) {
    List list;

    make_empty(&list);

    insert(list, header(list), 1);
    insert(list, header(list), 2);
    insert(list, header(list), 3);
    print_list(list); puts("");

    insert(list, footer(list), 4);
    insert(list, footer(list), 5);
    insert(list, footer(list), 6);
    print_list(list); puts("");

    insert(list, NULL, 7);
    insert(list, NULL, 8);
    insert(list, NULL, 9);
    print_list(list); puts("");

    Position find_1 = find(list, 1);
    printf("find_1  =>  %-4d\n", retrieve(find_1));

    Position next_1 = next(find_1);
    printf("next_1  =>  %-4d\n", retrieve(next_1));

    Position del_1 = delete(find_1);
    print_list(list); puts("");

    Position find_7 = find(list, 7);
    printf("del1 == find_7  =>  %d\n", del_1 == find_7);

    Position find_4 = find(list, 4);
    insert(list, find_4, 1);
    print_list(list); puts("");

    destroy_list(&list);
    printf("list = %#.8X\n", (int)list);

    return 0;
}

/* Method Definition */
void make_empty(List *list) {
    *list = (List)malloc(sizeof(list_t));

    (*list)->header = NULL;
    (*list)->footer = NULL;
}

Position insert(List list, Position pos, DataType data) {
    if (list->header == NULL) {
        // first data
        list->header = new_list_node(data, NULL, NULL);
        list->footer = list->header;
        return list->header;
    } else if (pos != NULL) { // center node
        ListNode new_node = new_list_node(data, pos->prev, pos);
        pos->prev = new_node;

        if (new_node->prev == NULL) {
            // update header pointer
            list->header = new_node;
        } else {
            new_node->prev->next = new_node;
        }

        return new_node;
    } else { // footer
        footer(list)->next = new_list_node(data, footer(list), NULL);
        list->footer = footer(list)->next;

        return footer(list);
    }
}

Position header(const List list) {
    return list->header;
}

Position footer(const List list) {
    return list->footer;
}

Position find(const List list, const DataType data) {
    for (ListNode c = list->header; c != NULL; c = c->next) {
        if (c->data == data) {
            return c;
        }
    }
    return NULL;
}

Position next(Position pos) {
    return pos->next;
}

DataType retrieve(Position pos) {
    return pos->data;
}

Position delete(Position pos) {
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;

    Position pos_next = pos->next;
    free(pos);

    return pos_next;
}

void destroy_list(List *list) {
    for (Position curr = header(*list)->next; curr != NULL; curr = curr->next) {
        free(curr->prev);
    }
    free(footer(*list));
    free(*list);

    *list = NULL;
}

static ListNode new_list_node(DataType data, ListNode prev, ListNode next) {
    ListNode node = (ListNode)malloc(sizeof(list_node_t));

    node->data = data;
    node->prev = prev;
    node->next = next;

    return node;
}

void print_list(const List list) {
    for (ListNode c = list->header; c != NULL; c = c->next) {
        printf("%-4d", c->data);
    }
}
