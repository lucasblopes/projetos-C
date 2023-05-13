#include <stdio.h>
#include <stdlib.h>

struct Node {

    struct Node *parent;
    struct Node *left;
    struct Node *right;
    char color;
    int key;
};

/* aloca memoria para um novo nodo */
struct Node *new_node(int key) {

    struct Node *node = malloc(sizeof(struct Node));
    if (!node) {
        perror("Error on malloc!\n");
        exit(1);
    }

    node->key = key;
    node->color = 'r'; /* 'r' */
    node->parent = NULL;
    node->right = NULL;
    node->left = NULL;
    return node;
}

/* libera memoria da arvore */
void free_tree(struct Node *node) {

    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

/* realiza a caminhada em ordem na arvore e imprime as chaves */
void inorder_print(struct Node *node, int level) {

    if (node) {
        inorder_print(node->left, level + 1);
        printf("(%c)%d,%d\n", node->color, node->key, level);
        inorder_print(node->right, level + 1);
    }
}

struct Node *tree_search(struct Node *node, int key) {

    if (!node)
        return NULL;

    if (node->key == key)
        return node;

    if (key < node->key)
        return tree_search(node->left, key);
    else 
        return tree_search(node->right, key);
}

/* retorna o maior nodo de uma arvore binaria */
struct Node *tree_minimum(struct Node *node) {

    if (node->left == NULL)
        return node;
    else
        return tree_minimum(node->left);
}

/* rotacao esquerda de uma sub-arvore */
struct Node* left_rotate(struct Node* root, struct Node* node) {

    struct Node* right_child = node->right;
    node->right = right_child->left;

    if (right_child->left != NULL) {
        right_child->left->parent = node;
    }

    right_child->parent = node->parent;

    if (node->parent == NULL) {
        root = right_child;
    } else if (node == node->parent->left) {
        node->parent->left = right_child;
    } else {
        node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;

    return root;
}

/* rotacao direita de uma sub-arvore */
struct Node* right_rotate(struct Node* root, struct Node* node) {

    struct Node* left_child = node->left;
    node->left = left_child->right;

    if (left_child->right != NULL) {
        left_child->right->parent = node;
    }

    left_child->parent = node->parent;

    if (node->parent == NULL) {
        root = left_child;
    } else if (node == node->parent->left) {
        node->parent->left = left_child;
    } else {
        node->parent->right = left_child;
    }

    left_child->right = node;
    node->parent = left_child;

    return root;
}

/* corrige a arvore para respeitar as propriedades da rb */
struct Node *rb_insert_fixup(struct Node *root, struct Node *node) {

    while (node->parent != NULL && node->parent->color == 'r') {
        struct Node *parent = node->parent;
        struct Node *grandparent = parent->parent;

        if (parent == grandparent->left) {
            struct Node *uncle = grandparent->right;

            /* caso 1: O tio é vermelho */
            if (uncle != NULL && uncle->color == 'r') {
                parent->color = 'b';
                uncle->color = 'b';
                grandparent->color = 'r';
                node = grandparent; /* move para o avo */
            } else {
                /* caso 2: O tio eh preto (ou inexistente) */ 
                if (node == parent->right) {
                    node = parent;
                    root = left_rotate(root, node);  
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                /* caso 3: O pai eh vermelho */
                parent->color = 'b';
                grandparent->color = 'r';
                root = right_rotate(root, grandparent);  
            }
        } else {
            struct Node *uncle = grandparent->left;

            /* caso 1: O tio é vermelho */
            if (uncle != NULL && uncle->color == 'r') {
                parent->color = 'b';
                uncle->color = 'b';
                grandparent->color = 'r';
                node = grandparent; /* move para o avo */
            } else {
                /* caso 2: O tio eh preto (ou inexistente) */
                if (node == parent->left) {
                    node = parent;
                    root = right_rotate(root, node);  
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                /* caso 3: O pai eh vermelho */
                parent->color = 'b';
                grandparent->color = 'r';
                root = left_rotate(root, grandparent);  
            }
        }
    }

    root->color = 'b'; /* raiz sempre preta */
    return root;
}

/* realiza a inclusao que nem a bst e corrige se preciso */
struct Node *rb_insert(struct Node *root, int key) {

    struct Node *new = new_node(key);
    struct Node *parent = NULL;
    struct Node *temp = root;

    while (temp != NULL) {
        parent = temp;
        if (key < temp->key)
            temp = temp->left;
        else if (key > temp->key)
            temp = temp->right;
        else {
            return root;
        }
    }

    new->parent = parent;

    if (parent == NULL) {
        root = new;
    } else if (key < parent->key) {
        parent->left = new;
    } else {
        parent->right = new;
    }

    root = rb_insert_fixup(root, new);

    return root;
}

void transplant(struct Node *node, struct Node *new) {

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = new;
        else
            node->parent->right = new;
        if (new)
            new->parent = node->parent;
    }
}
 
struct Node *rb_remove(struct Node* root, int key) {

    struct Node *node = tree_search(root, key);
    if (!node)
        return root;

    if (node->left == NULL) {
        transplant(node, node->right);
    } else {
        if (node->right == NULL) {
            transplant(node, node->left);
        }
        else {
            struct Node *s = tree_minimum(node->right); /* sucessor */
            node->key = s->key;
            root = rb_remove(node->right, s->key);
        }
    }
    free(node);

    return root;
}



int main() {

    struct Node *root = NULL;
    char op;
    int key;

    while (scanf("%c %d", &op, &key) == 2) {

        if (op == 'i') 
            root = rb_insert(root, key);
        else 
        if (op == 'r')
            root = rb_remove(root, key);
        getchar(); /* '/n' */
    }
    
    inorder_print(root, 0);    
    free_tree(root);

    return 0;
}