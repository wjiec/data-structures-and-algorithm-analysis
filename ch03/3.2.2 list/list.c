#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* List Structure Definition */
typedef int DataType;
struct _list_node_t {
    DataType data;
    struct _list_node_t *next;
};
typedef struct _list_node_t list_node_t;
typedef list_node_t *List;
typedef list_node_t *Position;


/* Methods for List */
void make_empty(List *list);
bool is_empty(const List list);
bool is_last(List list, Position pos);
Position find(List list, const DataType data);
void delete(List list, const DataType data);
Position find_previous(List list, const DataType data);
void insert(List list, const Position pos, const DataType data);
void destroy_list(List *list);
Position header(const List list);
Position footer(const List list);
Position next(Position pos);
DataType retrieve(Position pos);
void print_list(const List list);


/* Main Entry */
int main(void) {
    List list = NULL;

    // create list
    make_empty(&list);

    // insert to header
    insert(list, header(list), 1);
    insert(list, header(list), 2);
    insert(list, header(list), 3);

    // print list
    print_list(list);

    // insert to footer
    insert(list, footer(list), 4);
    insert(list, footer(list), 5);
    insert(list, footer(list), 6);

    // print list
    print_list(list);

    // find 5
    Position pos_5 = find(list, 5);
    printf("%d\n", retrieve(pos_5));

    // find 5 prev
    Position pos_5_prev = find_previous(list, 5);
    printf("%d\n", retrieve(pos_5_prev));

    // insert to pos_5_prev
    insert(list, pos_5_prev, 7);
    insert(list, pos_5_prev, 8);
    insert(list, pos_5_prev, 9);

    // print list
    print_list(list);

    // delete first
    delete(list, 3);
    print_list(list);

    // delete end
    delete(list, 6);
    print_list(list);

    // check is end
    printf("%d\n", is_last(list, pos_5));

    Position next_5 = next(pos_5);
    printf("%d\n", next_5 == NULL);


    // destroy list
    destroy_list(&list);

    printf("%#p\n", list);

    return 0;
}


/* Methods Definition */
void make_empty(List *list) {
    *list = (List)malloc(sizeof(list_node_t));

    (*list)->data = -1;
    (*list)->next = NULL;
}

bool is_empty(const List list) {
    if (list == NULL || list->next == NULL) {
        return true;
    }
    return false;
}

bool is_last(List list, Position pos) {
    if (footer(list) == pos && pos->next == NULL) {
        return true;
    }
    return false;
}

Position find(List list, const DataType data) {
    if (is_empty(list)) {
        return NULL;
    }

    for (Position curr = list->next; curr != NULL; curr = curr->next) {
        if (curr->data == data) {
            return curr;
        }
    }
    return NULL;
}

void delete(List list, const DataType data) {
    Position prev_item = find_previous(list, data);
    if (prev_item == NULL) {
        return;
    }

    Position del_item = prev_item->next;
    prev_item->next = del_item->next;
    free(del_item);
}

Position find_previous(List list, const DataType data) {
    if (is_empty(list)) {
        return NULL;
    }

    for (Position prev = list; prev->next != NULL; prev = prev->next) {
        if (prev->next->data == data) {
            return prev;
        }
    }
    return NULL;
}

void insert(List list, const Position pos, const DataType data) {
    list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
    node->data = data;

    if (header(list) == pos) {
        node->next = pos;
        list->next = node;
        return;
    }

    if (footer(list) == pos) {
        node->next = NULL;
        pos->next = node;
        return;
    }

    for (Position prev = list->next; prev->next != NULL; prev = prev->next) {
        if (prev->next == pos) {
            node->next = prev->next;
            prev->next = node;
            return;
        }
    }

    fprintf(stderr, "insert to list error occurs");
    exit(1);
}

void destroy_list(List *list) {
    Position tmp;
    for (Position curr = (*list)->next; curr != NULL; ) {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }

    *list = NULL;
}

Position header(const List list) {
    return list->next;
}

Position footer(const List list) {
    Position prev = list;

    while (prev->next != NULL) {
        prev = prev->next;
    }

    return prev;
}

Position next(Position pos) {
    return pos->next;
}

DataType retrieve(Position pos) {
    return pos->data;
}

void print_list(const List list) {
    for (Position curr = list->next; curr != NULL; curr = curr->next) {
        printf("%d ", curr->data);
    }
    printf("\n");
}
