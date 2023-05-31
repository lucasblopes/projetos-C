#include <stdio.h>
#include <stdlib.h>

enum Color {RED, BLACK};

struct Node {

    struct Node *parent;
    struct Node *left;
    struct Node *right;
    enum Color color;
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
    node->color = RED;
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

/* retorna 1 se todos os caminhos da raiz ate null tem a mesma quantidade de nodos pretos */
int equal_black_count(struct Node *root) {

    if (!root)
        return 1;

    int lb = root->color == BLACK ? equal_black_count(root->left) + 1 : equal_black_count(root->left);
    int rb = root->color == BLACK ? equal_black_count(root->right) + 1 : equal_black_count(root->right);

    return lb == rb;
}

/* retorna 1 se existem 2 nodos vermelhos consecutivos */
int consecutive_reds(struct Node *root) {

    if (!root)
        return 0;

    /* verifica se tem 2 nodos vermelhos consecutivos */
    if (root->color == RED && ((root->left && root->left->color == RED) ||
        (root->right && root->right->color == RED))) {
        return 1;
    }

    return consecutive_reds(root->left)+consecutive_reds(root->right) > 0;
}

/* retorna 1 se a arvore for rb */
int is_rb(struct Node *root) {

    if (root == NULL) 
        return 1;
    if (root->color == RED)
        return 0;

    return equal_black_count(root)*(!consecutive_reds(root));
}

struct Node *find_sucessor(struct Node *root, int key) {

    struct Node *aux = root;

    /* busca a chave */
    while (aux && aux->key != key) {
        if (key < aux->key)
            aux = aux->left;
        else 
            aux = aux->right;
    }
    /* busca o sucessor */
    if (!aux)
        return NULL;

    struct Node *s = aux;
    aux = aux->right;
    while (aux) {
        s = aux;
        aux = aux->left;
    }

    return s;
}

char print_color(int c){

    if (c == RED)   
        return 'R';
    if (c == BLACK)
        return 'B';

    return;
}

/* realiza a caminhada em ordem na arvore e imprime as chaves */
void inorder_print(struct Node *node, int level) {

    if (node) {
        inorder_print(node->left, level + 1);
        printf("(%c)%d,%d\n", print_color(node->color), node->key, level);
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

    while (node->parent != NULL && node->parent->color == RED) {
        struct Node *parent = node->parent;
        struct Node *grandparent = parent->parent;

        if (parent == grandparent->left) {
            struct Node *uncle = grandparent->right;

            /* caso 1: O tio é vermelho */
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
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
                parent->color = BLACK;
                grandparent->color = RED;
                right_rotate(root, grandparent);  
            }
        } else {
            struct Node *uncle = grandparent->left;

            /* caso 1: O tio é vermelho */
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
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
                parent->color = BLACK;
                grandparent->color = RED;
                left_rotate(root, grandparent);  
            }
        }
    }

    (*root)->color = BLACK; /* raiz sempre preta */
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

    while (x && *root && x->color == BLACK) {
        if (x == x->parent->left) {
            struct Node *w = x->parent->right;
            if (w && w->color == RED) {
                w->color = BLACK;                         /* caso 1 */
                x->parent->color = RED;                 /* caso 1 */
                left_rotate(root, x->parent);           /* caso 1 */
                w = x->parent->right;                   /* caso 1 */
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;                          /* caso 2 */
                x = x->parent;                           /* caso 2 */
            } else if (w->right->color == BLACK) {
                    w->left->color = BLACK;                /* caso 3 */
                    w->color = RED;                      /* caso 3 */
                    right_rotate(root, w);               /* caso 3 */
                    w = x->parent->right;                /* caso 3 */
            }
            w->color = x->parent->color;                 /* caso 4 */
            x->parent->color = BLACK;                      /* caso 4 */
            w->right->color = BLACK;                       /* caso 4 */
            left_rotate(root, x->parent);                /* caso 4 */
            x = *root;                                   /* caso 4 */
        } else {
            struct Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;                          /* caso 1 */
                x->parent->color = RED;                  /* caso 1 */
                right_rotate(root, x->parent);           /* caso 1 */
                w = x->parent->left;                     /* caso 1 */
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;                          /* caso 2 */
                x = x->parent;                           /* caso 2 */
            } else if (w->left->color == BLACK) {
                    w->right->color = BLACK;               /* caso 3 */
                    w->color = RED;                      /* caso 3 */
                    left_rotate(root, w);                /* caso 3 */
                    w = x->parent->left;                 /* caso 3 */
            }
            w->color = x->parent->color;                 /* caso 4 */
            x->parent->color = BLACK;                      /* caso 4 */
            w->left->color = BLACK;                        /* caso 4 */
            right_rotate(root, x->parent);               /* caso 4 */
            x = *root;                                   /* caso 4 */
        }
    }
    if (x)
        x->color = BLACK;
}

void rb_remove(struct Node **root, int key) {

    struct Node *z = tree_search(*root, key); /* nodo a ser removido */
    if (!z)
        return;

    struct Node *y = z; /* sucessor de z */
    struct Node *x; /* irmao de z */
    char y_original_color = y->color;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x)
                x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            if (y->right)
                y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK)
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
        if (op == RED)
            rb_remove(&root, key);
        getchar(); /* '/n' */
    }
    
    inorder_print(root, 0);    
    if (is_rb(root) == 1) 
        printf("red black valida\n");
    else    
        printf("red black invalida\n");
    free_tree(root);

    return 0;
}