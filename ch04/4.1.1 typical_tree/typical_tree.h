#ifndef __TYPICAL_TREE_INCLUDED__
#define __TYPICAL_TREE_INCLUDED__

#include <stddef.h>
#include <stdbool.h>

#include "fs_node.h"


typedef FsNode TypicalTreeData;

struct typical_tree_t;
typedef struct typical_tree_t *TypicalTree;


TypicalTree createTypicalTree(TypicalTreeData data);

TypicalTree insertSibling(TypicalTree tree, TypicalTreeData data);
TypicalTree insertChildren(TypicalTree tree, TypicalTreeData data);

size_t removeSibling(TypicalTree tree, TypicalTreeData data);
size_t removeChildren(TypicalTree tree, TypicalTreeData data);

TypicalTree findByName(TypicalTree tree, char *name);
TypicalTreeData retrieveData(TypicalTree tree);

void destroyTypicalTree(TypicalTree *tree);


#endif // __TYPICAL_TREE_INCLUDED__