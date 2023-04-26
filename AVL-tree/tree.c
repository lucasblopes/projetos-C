#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define max(a,b) (((a)>(b))?(a):(b))

struct tNode *new_node(int key) {

    struct tNode *node = malloc(sizeof(struct tNode));
    if (!node) {
        perror("Error on malloc!\n");
        exit(1);
    }

    node->key = key;
    node->height = 0;
    node->parent = NULL;
    node->right = NULL;
    node->left = NULL;
    return node;
}

void free_tree(struct tNode *node) {

    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int depth(struct tNode *node) {

    if (!node)
        return;

    if (!node->parent)
        return 0;

    node->height = depth(node->parent) + 1;
}

void inorder_walk(struct tNode *node) {

    if (node) {
        inorder_walk(node->left);
        printf("%d,%d\n", node->key, node->height);
        inorder_walk(node->right);
    }
}

int height(struct tNode *p) {

    int hl, hr;

    if (!p)
        return -1;
    
    hl = height(p->left);
    hr = height(p->right);

    if(hl > hr)
        return hl+1;
    else
        return hr+1;
}

struct tNode *max_node(struct tNode *node) {

    if (node->right == NULL)
        return node;
    else
        return max_node(node->right);
}

/* binary search */
struct tNode *search(struct tNode *node, int key) {

    if (!node)
        return NULL;

    if (node->key == key)
        return node;

    if (key < node->key)
        return search(node->left, key);
    else 
        return search(node->right, key);
}

struct tNode *left_rotation(struct tNode *p) {

    struct tNode* q = p->right;

    p->right = q->left;
    q->parent = p->parent;
    p->parent = q;

    if (q->left)
        q->left->parent = p;

    q->left = p;

    /* atualiza as alturas quando rotacionar */
    q->height = height(q);
    p->height = height(p);

    return q;
}

struct tNode *right_rotation(struct tNode *p) {

    struct tNode *q = p->left;

    p->left = q->right;
    q->parent = p->parent;
    p->parent = q;

    if (q->right)
        q->right->parent = p;

    q->right = p;
    
    /* atualiza as alturas quando rotacionar */
    q->height = height(q);
    p->height = height(p);

    return q;
}

/* retorna a diferenca de nivel do nodo esquerdo e do direito, de um pai */
int balance_factor(struct tNode* p) {

    if (!p)
        return 0;

    return (height(p->left) - height(p->right));
}

struct tNode* tree_balance(struct tNode* node) {

    if (balance_factor(node) < -1 && balance_factor(node->right) <= 0) { /* LL */
        return left_rotation(node);
    }

    if (balance_factor(node) > 1 && balance_factor(node->left) >= 0) { /* RR */
        return right_rotation(node);
    }

    if (balance_factor(node) > 1 && balance_factor(node->left) < 0) { /* LR */
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }

    if (balance_factor(node) < -1 && balance_factor(node->right) > 0) { /* RL */
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

    return node;
}

struct tNode *node_include(struct tNode *node, int key) {

    if (!node)
        return new_node(key);
    if (key < node->key) {
        node->left = node_include(node->left, key);
        node->left->parent = node; 
    }
    else {
        node->right = node_include(node->right, key);
        node->right->parent = node;
    }

    node->height = height(node);
    node = tree_balance(node);

    return node; 
}

void transplant(struct tNode *node, struct tNode *new) {

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = new;
        else
            node->parent->right = new;
        if (new)
            new->parent = node->parent;
    }
}

struct tNode *node_remove(struct tNode *node, int key) {

    struct tNode *parent, *a; /* antecessor */

    if (!node)
        return NULL;

    parent = node->parent;

    if (node->key == key) {
        if(!node->left) {
            transplant(node, node->right);
            free(node);
        } 
        else {
        if (!node->right) {
            transplant(node, node->left);
            free(node);
        } else {
            a = max_node(node->left);
            transplant(a, a->left);
            a->left = node->left;
            a->right = node->right;
            if (!parent) {
                a->parent = NULL;
                node->left->parent = a;
                node->right->parent = a;
            } else 
                transplant(node, a);
            free(node);
            parent = a;
        }
    }
    } else {
        if (key < node->key)
            node->left = node_remove(node->left, key);
        else
            node->right = node_remove(node->right, key);
    }

    if (parent) {
        parent->height = height(parent);
        parent = tree_balance(parent);
    }
    
    return parent;
}
