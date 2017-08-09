#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define HEAP_SIZE 1024
#define DE_POS(__pos) (list_heap[(__pos)])
#define ERROR_EXIT(Fmt, Arg...) do {\
    fprintf(stderr, Fmt, ##Arg);\
    exit(1);\
} while (0)


typedef int Position;
typedef int DataType;
struct _list_node_t {
    DataType data;
    Position next;
};
typedef struct _list_node_t list_node_t;
typedef list_node_t Node;
typedef int List;


static Node list_heap[HEAP_SIZE];
/* Heap Methods */
void init_heap();
Position list_alloc(void);
void list_free(Position pos);
/* List Methods */
List create_list();
bool is_empty(const List list);
bool is_last(Position pos);
Position header(const List list);
Position footer(const List list);
void insert_node(Position pos, DataType data);
Position find_node(const List list, DataType data);
DataType retrieve(Position pos);
void delete_node(List list, Position pos);
void destroy_list(List *list);

void print_list(const List list);
int get_free_info(void);


int main(void) {
    init_heap();
    printf("Free Heap Size => %d\n", get_free_info());

    puts("");
    List list = create_list();
    printf("list is empty => %d\n", is_empty(list));
    printf("Free Heap Size => %d\n", get_free_info());

    puts("");
    insert_node(header(list), 1);
    insert_node(header(list), 2);
    insert_node(header(list), 3);
    print_list(list); puts("");
    printf("Free Heap Size => %d\n", get_free_info());

    puts("");
    insert_node(footer(list), 4);
    insert_node(footer(list), 5);
    insert_node(footer(list), 6);
    print_list(list); puts("");
    printf("Free Heap Size => %d\n", get_free_info());

    puts("");
    Position find_6 = find_node(list, 6);
    printf("find_6 is last => %d\n", is_last(find_6));

    puts("");
    Position find_4 = find_node(list, 4);
    printf("find_4 => %d\n", retrieve(find_4));

    puts("");
    delete_node(list, find_4);
    print_list(list); puts("");
    printf("Free Heap Size => %d\n", get_free_info());

    puts("");
    destroy_list(&list);
    printf("Free Heap Size => %d\n", get_free_info());

    puts("");
    printf("list => %d\n", list);

    return 0;
}

void init_heap() {
    for (int i = 0; i < HEAP_SIZE; ++i) {
        list_heap[i].next = i + 1;
    }
    list_heap[HEAP_SIZE - 1].next = 0;
}

Position list_alloc(void) {
    Position alloc_pos = list_heap[0].next;

    list_heap[0].next = list_heap[alloc_pos].next;
    return alloc_pos;
}

void list_free(Position pos) {
    list_heap[pos].next = list_heap[0].next;
    list_heap[0].next = pos;
}

List create_list() {
    List new_list = DE_POS(0).next;

    DE_POS(0).next = DE_POS(new_list).next;
    DE_POS(new_list).next = 0;

    return new_list;
}

bool is_empty(const List list) {
    return DE_POS(list).next == 0;
}

bool is_last(Position pos) {
    return DE_POS(pos).next == 0;
}

Position header(const List list) {
    return list;
}

Position footer(const List list) {
    Position curr = list;
    while (DE_POS(curr).next != 0) {
        curr = DE_POS(curr).next;
    }
    return curr;
}

void insert_node(Position pos, DataType data) {
    Position new_node = list_alloc();

    DE_POS(new_node).data = data;
    DE_POS(new_node).next = DE_POS(pos).next;
    DE_POS(pos).next = new_node;
}

Position find_node(const List list, DataType data) {
    for (Position c = DE_POS(list).next; c != 0; c = DE_POS(c).next) {
        if (DE_POS(c).data == data) {
            return c;
        }
    }
    return 0;
}

DataType retrieve(Position pos) {
    if (pos == 0) {
        ERROR_EXIT("cannot access position 0");
    }
    return DE_POS(pos).data;
}

void delete_node(List list, Position pos) {
    if (pos == 0) {
        ERROR_EXIT("cannot delete position 0");
    }

    Position prev = list;
    while (prev != 0 && DE_POS(prev).next != pos) {
        prev = DE_POS(prev).next;
    }

    DE_POS(prev).next = DE_POS(pos).next;
    list_free(pos);
}

void destroy_list(List *list) {
    Position curr = *list;
    for (Position idx = DE_POS(curr).next, next; idx != 0;) {
        next = DE_POS(idx).next;
        list_free(idx);
        idx = next;
    }

    list_free(*list);
    *list = 0;
}

void print_list(const List list) {
    for (Position c = DE_POS(list).next; c != 0; c = DE_POS(c).next) {
        printf("%-4d", DE_POS(c).data);
    }
}

int get_free_info(void) {
    int size = 0;

    for (Position c = 0; DE_POS(c).next != 0; c = DE_POS(c).next) {
        size += 1;
    }

    return size;
}
