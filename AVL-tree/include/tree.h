#ifndef TREE_H
#define TREE_H

/* struct de um nodo de uma arvore avl */
struct tNode {
    
    struct tNode *parent;
    struct tNode *right;
    struct tNode *left;
    int key, height;
};

struct tNode *node_insert(struct tNode *node, int key);

struct tNode *node_remove(struct tNode *node, int key); 

void inorder_print(struct tNode *node, int level);

void free_tree(struct tNode *node);

#endif