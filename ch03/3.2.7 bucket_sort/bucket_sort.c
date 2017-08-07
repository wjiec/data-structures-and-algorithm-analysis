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
        // initializing bucket size
        int origin_size[10] = { 0 };
        for (int i = 0; i < 10; ++i) {
            origin_size[i] = bucket_array[i]->bucket_size;
        }

        for (int i = 0; i < 10; ++i) {
            if (bucket_array[i]->bucket_size == 0) {
                continue;
            }

            BucketNode c;
            int next_idx = 0;
            while (origin_size[i]--) {
                // reassign next node
                c = bucket_array[i]->bucket;

                // calc next bucket
                next_idx = c->calc_value % 10;
                c->calc_value /= 10;

                // replace node
                bucket_array[i]->bucket = c->next;
                bucket_array[i]->bucket_size -= 1;
                bucket_node_append(bucket_array + next_idx, c);
            }
        }
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
    node->next = NULL;

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

