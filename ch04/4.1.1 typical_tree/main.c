#include <stdio.h>
#include <stdlib.h>

#include "typical_tree.h"
#include "fs_node.h"


int main(void) {
    TypicalTreeData root_dir = createNode("usr", 4, true);
    TypicalTree tree = createTypicalTree(root_dir);

    {
        TypicalTreeData usr_bin = createNode("bin", 4, true);
        TypicalTree bin = insertChildren(tree, usr_bin);

        TypicalTreeData usr_sbin = createNode("sbin", 4, true);
        TypicalTree sbin = insertChildren(tree, usr_sbin);

        TypicalTreeData usr_local = createNode("local", 4, true);
        TypicalTree local = insertSibling(sbin, usr_local);

        TypicalTreeData bin_dc = createNode("dc", 100, false);
        insertChildren(bin, bin_dc);

        TypicalTreeData bin_ls = createNode("ls", 50, false);
        insertChildren(bin, bin_ls);

        TypicalTreeData sbin_docker = createNode("docker", 80, false);
        insertChildren(sbin, sbin_docker);

        TypicalTreeData local_nginx = createNode("nginx", 4, true);
        insertChildren(local, local_nginx);

        TypicalTreeData local_gcc = createNode("gcc", 4, true);
        insertChildren(local, local_gcc);
    }

    {
        TypicalTree node = findByName(tree, "ls");
        TypicalTreeData ls_data = retrieveData(node);
        printf("find[ls] => %s\n", getNodeName(ls_data));
    }

    {
        TypicalTree dc = findByName(tree, "dc");
        TypicalTreeData ls = retrieveData(findByName(tree, "ls"));
        removeSibling(dc, ls);
    }

    {
        TypicalTree local = findByName(tree, "local");
        TypicalTreeData gcc = retrieveData(findByName(tree, "gcc"));

        removeChildren(local, gcc);
    }

    destroyTypicalTree(&tree);
    printf("tree = %p\n", tree);

    return 0;
}
