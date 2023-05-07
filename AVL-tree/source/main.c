#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main() {

    struct tNode *root = NULL;
    char op;
    int key;

    while (scanf("%c %d", &op, &key) == 2) {

        if (op == 'i')
            root = node_insert(root, key);
        else 
        if (op == 'r')
            root = node_remove(root, key);
        getchar(); /* '/n' */
    }

    inorder_print(root, 0);    
    free_tree(root);

    return 0;
}