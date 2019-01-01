#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typical_tree.h"


struct typical_tree_t {
    FsNode node;
    TypicalTree next_sibling;
    TypicalTree first_children;
};


static void doPrintTypicalTree(FILE *fp, TypicalTree tree, int depth);
static int doPrintTypicalSize(FILE *fp, TypicalTree tree, int depth);


TypicalTree createTypicalTree(TypicalTreeData data) {
    TypicalTree tree = (TypicalTree)malloc(sizeof(struct typical_tree_t));
    tree->node = data;

    tree->next_sibling = NULL;
    tree->first_children = NULL;

    return tree;
}

TypicalTree insertSibling(TypicalTree tree, TypicalTreeData data) {
    TypicalTree node = createTypicalTree(data);

    TypicalTree pos = tree;
    while (pos->next_sibling != NULL) {
        pos = pos->next_sibling;
    }
    pos->next_sibling = node;

    return node;
}

TypicalTree insertChildren(TypicalTree tree, TypicalTreeData data) {
    if (tree->first_children == NULL) {
        TypicalTree node = createTypicalTree(data);

        tree->first_children = node;
        return node;
    }

    return insertSibling(tree->first_children, data);
}

size_t removeSibling(TypicalTree tree, TypicalTreeData data) {
    if (!tree->next_sibling) {
        return 0;
    }

    TypicalTree node = tree;
    while (node->next_sibling) {
        TypicalTreeData node_data = retrieveData(node->next_sibling);
        if (strcmp(getNodeName(node_data), getNodeName(data)) == 0) {
            break;
        }

        node = node->next_sibling;
    }

    if (node->next_sibling) {
        TypicalTree del_node = node->next_sibling;
        node->next_sibling = del_node->next_sibling;

        destroyTypicalTree(&del_node);
        return 1;
    }

    return 0;
}

size_t removeChildren(TypicalTree tree, TypicalTreeData data) {
    if (!tree->first_children) {
        return 0;
    }

    return removeSibling(tree->first_children, data);
}

TypicalTree findByName(TypicalTree tree, char *name) {
    TypicalTree node = tree;
    while (node) {
        TypicalTreeData node_data = retrieveData(node);
        if (strcmp(getNodeName(node_data), name) == 0) {
            return node;
        }

        if (node->first_children) {
            TypicalTree  result = findByName(node->first_children, name);
            if (result) {
                return result;
            }
        }

        node = node->next_sibling;
    }

    return NULL;
}

TypicalTreeData retrieveData(TypicalTree tree) {
    return tree->node;
}

void destroyTypicalTree(TypicalTree *tree) {
    if ((*tree)->first_children) {
        destroyTypicalTree(&((*tree)->first_children));
    }

    if ((*tree)->next_sibling) {
        destroyTypicalTree(&((*tree)->next_sibling));
    }

    free((*tree)->node);
    free(*tree);
    *tree = NULL;
}

void printTypicalTree(FILE *fp, TypicalTree tree) {
    if (tree == NULL) {
        fprintf(fp, "tree empty\n");
    } else {
        doPrintTypicalTree(fp, tree, 0);
    }
}

static void doPrintTypicalTree(FILE *fp, TypicalTree tree, int depth) {
    fprintf(fp, "%*c%s\n", depth + 1, ' ', getNodeName(retrieveData(tree)));

    // children
    if (tree->first_children) {
        doPrintTypicalTree(fp, tree->first_children, depth + 1);
    }

    // sibling
    if (tree->next_sibling) {
        doPrintTypicalTree(fp, tree->next_sibling, depth);
    }
}

int printTypicalSize(FILE *fp, TypicalTree tree) {
    if (tree == NULL) {
        fprintf(fp, "tree empty\n");
        return 0;
    }
    return doPrintTypicalSize(fp, tree, 0);
}

static int doPrintTypicalSize(FILE *fp, TypicalTree tree, int depth) {
    int size = getNodeSize(retrieveData(tree));
    if (tree->first_children) {
        size += doPrintTypicalSize(fp, tree->first_children, depth + 1);
    }

    fprintf(fp, "%*c%s(%d)\n", depth + 1, ' ', getNodeName(retrieveData(tree)), size);

    if (tree->next_sibling) {
        size += doPrintTypicalSize(fp, tree->next_sibling, depth);
    }

    return size;
}
