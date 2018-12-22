#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs_node.h"


struct fs_node_t {
    char *name;
    size_t size;
    bool is_directory;
};


FsNode createNode(char *name, size_t size, bool is_directory) {
    FsNode node = (FsNode)malloc(sizeof(struct fs_node_t));
    node->name = name;
    node->size = size;
    node->is_directory = is_directory;

    return node;
}

char *getNodeName(FsNode node) {
    return node->name;
}

size_t getNodeSize(FsNode node) {
    return node->size;
}

bool isDirectory(FsNode node) {
    return node->is_directory;
}
