#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#define MIN_QUEUE_SIZE 8
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


// queue.h
typedef int DataType;
typedef struct _queue_t queue_t;
typedef queue_t *Queue;

Queue create_queue(const size_t queue_size);
bool queue_is_full(const Queue queue);
bool queue_is_empty(const Queue queue);
size_t queue_get_size(const Queue queue);
DataType queue_get(Queue queue);
void queue_put(Queue queue, const DataType data);
void queue_destroy(Queue *queue);


// main.c
int main(void) {
    Queue queue = create_queue(4);

    assert(queue_get_size(queue) == 0);
    assert(queue_is_empty(queue) == true);

    queue_put(queue, 1);
    queue_put(queue, 2);
    queue_put(queue, 3);
    queue_put(queue, 4); // 1 2 3 4 * * * *
    assert(queue_get_size(queue) == 4);

    DataType get_data = queue_get(queue); // * 2 3 4 * * * *
    assert(get_data == 1);
    assert(queue_get_size(queue) == 3);

    queue_put(queue, 5);
    queue_put(queue, 6);
    queue_put(queue, 7);
    queue_put(queue, 8); // * 2 3 4 5 6 7 8
    assert(queue_get_size(queue) == 7);
    assert(queue_get(queue) == 2); // * * 3 4 5 6 7 8

    queue_put(queue, 1);
    queue_put(queue, 2); // 1 2 3 4 5 6 7 8
    assert(queue_get_size(queue) == 8);
    assert(queue_is_full(queue) == true);

    // put element to full queue
    // queue_put(queue, 0);

    assert(queue_get(queue) == 3);
    assert(queue_get(queue) == 4);
    assert(queue_get(queue) == 5);
    assert(queue_get(queue) == 6);
    assert(queue_get(queue) == 7);
    assert(queue_get(queue) == 8);
    assert(queue_get(queue) == 1);
    assert(queue_get(queue) == 2);
    assert(queue_is_empty(queue) == true);

    queue_destroy(&queue);
    assert(queue == NULL);

    return 0;
}


// queue.c [place in implementation file]
struct _queue_t {
    DataType *array;
    int queue_front;
    int queue_rear;
    size_t queue_size;
    size_t queue_capacity;
};

// Queue implementation by dynamically allocated array
Queue create_queue(const size_t queue_size) {
    Queue queue = (Queue)(malloc(sizeof(queue_t)));

    queue->queue_size = 0;
    queue->queue_front = 0;
    queue->queue_rear = 0;
    queue->queue_capacity = MAX(queue_size, MIN_QUEUE_SIZE);
    queue->array = (DataType*)malloc(sizeof(DataType) * queue->queue_capacity);

    return queue;
}

bool queue_is_full(const Queue queue) {
    return queue->queue_size == queue->queue_capacity;
}

bool queue_is_empty(const Queue queue) {
    return queue->queue_size == 0;
}

size_t queue_get_size(const Queue queue) {
    return queue->queue_size;
}

DataType queue_get(Queue queue) {
    if (queue_is_empty(queue)) {
        fprintf(stderr, "cannot get data from empty queue");
        exit(1);
    }

    DataType data = queue->array[queue->queue_front];
    if (queue->queue_front == queue->queue_capacity - 1) {
        queue->queue_front = 0;
    } else {
        queue->queue_front += 1;
    }
    queue->queue_size -= 1;
    return data;
}

void queue_put(Queue queue, const DataType data) {
    if (queue_is_full(queue)) {
        fprintf(stderr, "cannot put data to full queue");
        exit(1);
    }

    queue->array[queue->queue_rear] = data;
    if (queue->queue_rear == queue->queue_capacity - 1) {
        queue->queue_rear = 0;
    } else {
        queue->queue_rear += 1;
    }
    queue->queue_size += 1;
}

void queue_destroy(Queue *queue) {
    free((*queue)->array);
    free(*queue);
    *queue = NULL;
}
