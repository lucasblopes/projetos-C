#ifndef TREE_H
#define TREE_H

/* struct de um nodo de uma arvore avl */
struct tNode {

    struct tNode *parent;
    struct tNode *right;
    struct tNode *left;
    int key, height;
};

struct tNode *node_include(struct tNode *node, int key);

struct tNode *node_remove(struct tNode *node, int key); 

void reset_level(struct tNode *node);

void inorder_walk(struct tNode *node);

void free_tree(struct tNode *node);

#endif