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

void inorder_walk(struct tNode *node, int root_height) {

    if (node) {
        inorder_walk(node->left, root_height);
        printf("%d,%d\n", node->key, abs(node->height - root_height));
        inorder_walk(node->right, root_height);
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

struct tNode *min_node(struct tNode *node) {

    if (node->left == NULL)
        return node;
    else
        return min_node(node->left);
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
    //node->height = height(node); nao precisa (ne?)

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

struct tNode *transplant(struct tNode *node, struct tNode *new) {

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = new;
        else
            node->parent->right = new;
        if (new)
            new->parent = node->parent;
    }
}

void update_parent_height(struct tNode *p) {

    if(!p)
        return;

    p->height = height(p);
    update_parent_height(p->parent);
}

struct tNode *node_remove(struct tNode *node, struct tNode *root) {

    struct tNode *new_root = root, *parent = node->parent, *s; /* successor */

    if(!node->left) {
        transplant(node, node->right);
        free(node);
    } 
    else {
    if (!node->right) {
        transplant(node, node->left);
        free(node);
    } else {
        s = min_node(node->right);
        transplant(s, s->right);
        s->left = node->left;
        s->right = node->right;
        transplant(node, s);
        if (node == root)
            new_root = s;
        free(node);
        }
    }

    while (parent) {
        parent->height = height(parent);
        parent = parent->parent;
    }

    return new_root;
}