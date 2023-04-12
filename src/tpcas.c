#include "tree.h"
#include "ParseAsm.h"

extern Node *root;

int main(void) {
    if (tree_flag)
        printTree(root);
    return 0;
}
