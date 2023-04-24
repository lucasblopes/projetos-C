#ifndef TREE_H
#define TREE_H

struct tNode {

    struct tNode *parent;
    struct tNode *right;
    struct tNode *left;
    int key, height;
};

struct tNode *node_include(struct tNode *node, int key);

struct tNode *node_remove(struct tNode *node, struct tNode *root);

struct tNode *search(struct tNode *node, int key);

void inorder_walk(struct tNode *node);

void free_tree(struct tNode *node);

#endif