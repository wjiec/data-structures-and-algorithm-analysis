#include <stdio.h>
#include <stdlib.h>

struct _bucket_node_t {
    int source_value;
    int calc_value;
    struct _bucket_node_t *next;
};
typedef struct _bucket_node_t *BucketNode;

struct _bucket_t {
    BucketNode bucket;
    size_t bucket_size;
};
typedef struct _bucket_t *Bucket;


void bucket_sort(int array[], const size_t array_size);
void print_array(const int array[], const size_t array_size);

static void bucket_node_append(Bucket *bucket, BucketNode node);
static void bucket_to_array(Bucket *buckets, int array[]);
static void reset_bucket_node_array(Bucket array[], BucketNode node_array[]);

int main(void) {
    int array[] = { 0, 1, 512, 343, 64, 125, 216, 27, 8, 729 };
    print_array(array, 10); puts("");

    bucket_sort(array, 10);
    print_array(array, 10); puts("");

    return 0;
}


void bucket_sort(int array[], const size_t array_size) {
    Bucket bucket_array[10] = { NULL };
    BucketNode bucket_node_array =
            (BucketNode)(malloc(sizeof(struct _bucket_node_t) * array_size));

    // initializing bucket
    for (int i = 0; i < 10; ++i) {
        bucket_array[i] = (Bucket)(malloc(sizeof(struct _bucket_t)));
        bucket_array[i]->bucket = NULL;
        bucket_array[i]->bucket_size = 0;
    }

    // initializing bucket nodes
    for (int i = 0, init_idx; i < array_size; ++i) {
        bucket_node_array[i].source_value = array[i];
        bucket_node_array[i].calc_value = array[i] / 10;
        bucket_node_array[i].next = NULL;

        init_idx = bucket_node_array[i].source_value % 10;
        bucket_node_append(&(bucket_array[init_idx]), &(bucket_node_array[i]));
    }

    // foreach bits
    while (bucket_array[0]->bucket_size != array_size) {
        // @TODO bug current

//        reset_bucket_node_array(bucket_array, &bucket_node_array);
//
//        for (int i = 0, init_idx; i < array_size; ++i) {
//            init_idx = bucket_node_array[i].calc_value % 10;
//            bucket_node_array[i].calc_value /= 10;
//
//            bucket_node_append(&(bucket_array[init_idx]), &(bucket_node_array[i]));
//        }
    }

    // buckets to array
    bucket_to_array(bucket_array, array);
}

void print_array(const int array[], const size_t array_size) {
    for (int i = 0; i < array_size; ++i) {
        printf("%d\t", array[i]);
    }
}

static void bucket_node_append(Bucket *bucket, BucketNode node) {
    if ((*bucket)->bucket == NULL) {
        (*bucket)->bucket = node;
    } else {
        BucketNode curr = (*bucket)->bucket;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        curr->next = node;
    }

    (*bucket)->bucket_size += 1;
}

static void bucket_to_array(Bucket *buckets, int array[]) {
    for (int i = 0, idx = 0; i < 10; ++i) {
        if (buckets[i]->bucket_size != 0) {
            for (BucketNode c = buckets[i]->bucket; c != NULL; c = c->next) {
                array[idx++] = c->source_value;
            }
        }
    }
}

static void reset_bucket_node_array(Bucket array[], BucketNode node_array[]) {
    for (int i = 0, idx = 0; i < 10; ++i) {
        if (array[i]->bucket_size != 0) {
            for (BucketNode c = array[i]->bucket; c != NULL; c = c->next) {
                node_array[idx++] = c;
            }
        }
    }
}
