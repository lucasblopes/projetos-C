#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/* aloca memoria para um novo nodo */
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

/* libera memoria da arvore */
void free_tree(struct tNode *node) {

    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

/* realiza a caminhada em ordem na arvore */
void inorder_print(struct tNode *node, int level) {

    if (node) {
        inorder_print(node->left, level + 1);
        printf("%d,%d\n", node->key, level);
        inorder_print(node->right, level + 1);
    }
}

/* calcula a altura de um nodo */
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

/* retorna o maior nodo de uma arvore binaria */
struct tNode *max_node(struct tNode *node) {

    if (node->right == NULL)
        return node;
    else
        return max_node(node->right);
}

/* rotacao esquerda de uma sub-arvore */
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

/* rotacao direita de uma sub-arvore */
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

/* realiza o balancemento de uma arvore avl cobrindo todos os casos de rotacoes */
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

/* realiza a inclusao de um nodo em uma arvore avl e realiza o balanceamento, se necessario */
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

/* realiza o transplante de dois nodos, atualizando as suas hierarquias */
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

/* remove um nodo da arvore avl e realiza o balancemanto, se necessario */
struct tNode *node_remove(struct tNode* node, int key) {

    if (!node)
        return NULL;

    if (node->key == key) {
        if (!node->left) { /* remove nodo com no maximo um filho */
            struct tNode *temp = node->left ? node->left : node->right;
            transplant(node, temp);
            free(node);
            return temp;
        } else {    /* remove nodo com dois filhos usando o antecessor */
            struct tNode *anteccessor = max_node(node->left);
            node->key = anteccessor->key;
            node->left = node_remove(node->left, anteccessor->key);
            return node;
        }
    }
    /* busca binaria do nodo */
    if (key < node->key)
        node->left = node_remove(node->left, key);
    else
        node->right = node_remove(node->right, key);

    node->height = height(node);
    node = tree_balance(node);

    return node;
}