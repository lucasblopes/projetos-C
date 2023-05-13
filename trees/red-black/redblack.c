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
void left_rotate(struct Node **root, struct Node *node) {

    struct Node* right_child = node->right;
    node->right = right_child->left;

    if (right_child->left != NULL) {
        right_child->left->parent = node;
    }

    right_child->parent = node->parent;

    if (node->parent == NULL) {
        *root = right_child;
    } else if (node == node->parent->left) {
        node->parent->left = right_child;
    } else {
        node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;

}

/* rotacao direita de uma sub-arvore */
void right_rotate(struct Node **root, struct Node *node) {

    struct Node* left_child = node->left;
    node->left = left_child->right;

    if (left_child->right != NULL) {
        left_child->right->parent = node;
    }

    left_child->parent = node->parent;

    if (node->parent == NULL) {
        *root = left_child;
    } else if (node == node->parent->left) {
        node->parent->left = left_child;
    } else {
        node->parent->right = left_child;
    }

    left_child->right = node;
    node->parent = left_child;

}

/* corrige a arvore para respeitar as propriedades da rb */
void rb_insert_fixup(struct Node **root, struct Node *node) {

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
                    left_rotate(root, node);  
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                /* caso 3: O pai eh vermelho */
                parent->color = 'b';
                grandparent->color = 'r';
                right_rotate(root, grandparent);  
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
                    right_rotate(root, node);  
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                /* caso 3: O pai eh vermelho */
                parent->color = 'b';
                grandparent->color = 'r';
                left_rotate(root, grandparent);  
            }
        }
    }

    (*root)->color = 'b'; /* raiz sempre preta */
}

/* realiza a inclusao que nem a bst e corrige se preciso */
void rb_insert(struct Node **root, int key) {

    struct Node *new = new_node(key);
    struct Node *parent = NULL;
    struct Node *temp = *root;

    while (temp != NULL) {
        parent = temp;
        if (key < temp->key)
            temp = temp->left;
        else if (key > temp->key)
            temp = temp->right;
        else {
            return;
        }
    }

    new->parent = parent;

    if (parent == NULL) {
        *root = new;
    } else if (key < parent->key) {
        parent->left = new;
    } else {
        parent->right = new;
    }

    rb_insert_fixup(&(*root), new);

}

void transplant(struct Node **root, struct Node *node, struct Node *new) {

    if (!node->parent)
        *root = new;
    else if (node == node->parent->left)
        node->parent->left = new;
    else 
        node->parent->right = new;
    if (new)
        new->parent = node->parent;

}

void rb_delete_fixup(struct Node **root, struct Node *x) {

    while (x && *root && x->color == 'b') {
        if (x == x->parent->left) {
            struct Node *w = x->parent->right;
            if (w->color == 'r') {
                w->color = 'b';                         /* caso 1 */
                x->parent->color = 'r';                 /* caso 1 */
                left_rotate(root, x->parent);           /* caso 1 */
                w = x->parent->right;                   /* caso 1 */
            }
            if (w->left->color == 'b' && w->right->color == 'b') {
                w->color = 'r';                          /* caso 2 */
                x = x->parent;                           /* caso 2 */
            } else if (w->right->color == 'b') {
                    w->left->color = 'b';                /* caso 3 */
                    w->color = 'r';                      /* caso 3 */
                    right_rotate(root, w);               /* caso 3 */
                    w = x->parent->right;                /* caso 3 */
            }
            w->color = x->parent->color;                 /* caso 4 */
            x->parent->color = 'b';                      /* caso 4 */
            w->right->color = 'b';                       /* caso 4 */
            left_rotate(root, x->parent);                /* caso 4 */
            x = *root;                                   /* caso 4 */
        } else {
            struct Node *w = x->parent->left;
            if (w->color == 'r') {
                w->color = 'b';                          /* caso 1 */
                x->parent->color = 'r';                  /* caso 1 */
                right_rotate(root, x->parent);           /* caso 1 */
                w = x->parent->left;                     /* caso 1 */
            }
            if (w->right->color == 'b' && w->left->color == 'b') {
                w->color = 'r';                          /* caso 2 */
                x = x->parent;                           /* caso 2 */
            } else if (w->left->color == 'b') {
                    w->right->color = 'b';               /* caso 3 */
                    w->color = 'r';                      /* caso 3 */
                    left_rotate(root, w);                /* caso 3 */
                    w = x->parent->left;                 /* caso 3 */
            }
            w->color = x->parent->color;                 /* caso 4 */
            x->parent->color = 'b';                      /* caso 4 */
            w->left->color = 'b';                        /* caso 4 */
            right_rotate(root, x->parent);               /* caso 4 */
            x = *root;                                   /* caso 4 */
        }
    }
    if (x)
        x->color = 'b';
}

void rb_remove(struct Node **root, int key) {

    struct Node *node = tree_search(*root, key);
    if (!node)
        return;

    char original_color = node->color;
    struct Node *x; /* irmao de node */

    if (node->left == NULL) {
        x = node->right;
        transplant(root, node, node->right);
    } else {
        if (node->right == NULL) {
            x = node->left;
            transplant(root, node, node->left);
        }
        else {
            struct Node *y = tree_minimum(node->right); /* sucessor */
            original_color = y->color;
            x = y->right;
            if (y->parent == node)
                x->parent = y;
            else { 
                transplant(root, y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            transplant(root, node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
    }
    free(node);
    if (x && original_color == 'b')
        rb_delete_fixup(root, x);
}

int main() {

    struct Node *root = NULL;
    char op;
    int key;

    while (scanf("%c %d", &op, &key) == 2) {

        if (op == 'i') 
            rb_insert(&root, key);
        else 
        if (op == 'r')
            rb_remove(&root, key);
        getchar(); /* '/n' */
    }
    
    inorder_print(root, 0);    
    free_tree(root);

    return 0;
}