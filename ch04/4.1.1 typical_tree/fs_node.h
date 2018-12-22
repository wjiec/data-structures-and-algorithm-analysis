#ifndef __FILE_SYSTEM_NODE_INCLUDED__
#define __FILE_SYSTEM_NODE_INCLUDED__

#include <stddef.h>
#include <stdbool.h>


struct fs_node_t;
typedef struct fs_node_t *FsNode;

FsNode createNode(char *name, size_t size, bool is_directory);

char *getNodeName(FsNode node);
size_t getNodeSize(FsNode node);
bool isDirectory(FsNode node);



#endif // __FILE_SYSTEM_NODE_INCLUDED__
