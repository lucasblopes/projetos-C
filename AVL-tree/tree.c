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

struct tNode *minimum_value(struct tNode *node) {

    if (node->left == NULL)
        return node;
    else
        return minimum_value(node->left);
}

struct tNode *maximum_value(struct tNode *node) {

    if (node->right == NULL)
        return node;
    else
        return minimum_value(node->right);
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

    return height(p->left) - height(p->right);
}

struct tNode *tree_balance(struct tNode *node, int key) {

    
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

    /* ---- balanceamento ---- */
    node->height = height(node);

    if (balance_factor(node) > 1 && key < node->left->key) {
        return right_rotation(node);
    }

    if (balance_factor(node) > 1 && key > node->left->key) {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }

    if (balance_factor(node) < -1 && key > node->right->key) {
        return left_rotation(node);
    }

    if (balance_factor(node) < -1 && key < node->right->key) {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

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

struct tNode *node_remove(struct tNode *node, struct tNode *root) {

    struct tNode *new_root = root, *s; /* successor */

    if(!node->left) {
        transplant(node, node->right);
        free(node);
    } 
    else {
        if (!node->right) {
            transplant(node, node->left);
            free(node);
        }
        else {
            s = minimum_value(node->right);
            s = right_rotation(s->parent);
            left_rotation(node);
            s->left = node->left;
            node->left->parent = s;
            if (node == root)
                new_root = s;
            free(node);
            if (node == root)
                new_root = s;
            free(node);
        }
    }

    /* ---- balanceamento (nao funciona) ---- */
    root->height = height(root);

    if (balance_factor(root) > 1 && balance_factor(root->left) >= 0) { // LL
        return right_rotation(root);
    } 

    if (balance_factor(root) > 1 && balance_factor(root->left) < 0) { // LR
        root->left = left_rotation(root->left);
        return right_rotation(root);
    } 

    if (balance_factor(root) < -1 && balance_factor(root->right) <= 0) { // RR
        return left_rotation(root);
    } 
     
    if (balance_factor(root) < -1 && balance_factor(root->right) > 0) { // RL
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }

    return new_root;
}