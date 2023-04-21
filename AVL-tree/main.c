#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main() {

    struct tNode *root = NULL;
    char op;
    int key;

    while (scanf("%c %d", &op, &key) == 2) {

        if (op == 'i')
            root = node_include(root, key);
        else 
        if (op == 'r')
            root = node_remove(search(root, key), root);
        //root = tree_balance(root);
        getchar(); /* '/n' */
    }

    inorder_walk(root);
    printf("\n");
    
    free_tree(root);

    return 0;
}