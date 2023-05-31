#include <stdio.h>
#include <stdlib.h>

struct Node {

    struct Node *left;
    struct Node *right;
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
        printf("%d,%d\n", node->key, level);
        inorder_print(node->right, level + 1);
    }
}

/* retorna o maior nodo de uma arvore binaria */
struct Node *max_node(struct Node *node) {

    if (node->right == NULL)
        return node;
    else
        return max_node(node->right);
}

/* rotacao esquerda de uma sub-arvore */
struct Node *left_rotate(struct Node *p) {

    struct Node* q = p->right;
    p->right = q->left;
    q->left = p;

    return q;
}

/* rotacao direita de uma sub-arvore */
struct Node *right_rotate(struct Node *p) {

    struct Node *q = p->left;
    p->left = q->right;
    q->right = p;

    return q;
}

struct Node *splay_insert(struct Node *node, int key) {

    if (!node)
        return new_node(key);
    if (key < node->key) {
        node->left = splay_insert(node->left, key); 
        node = right_rotate(node);
    } else 
    if (key > node->key) {  
        node->right = splay_insert(node->right, key);
        node = left_rotate(node);
    }

    return node; 
}

struct Node *splay(struct  Node *root, int key) {

    if (root == NULL || root->key == key)
        return root;
 
    if (root->key > key) {
        if (root->left == NULL) 
            return root;
        if (root->left->key > key) {     /* zig-zig (left-left) */
            root->left->left = splay(root->left->left, key);
            root = right_rotate(root);
        } else if (root->left->key < key) {     /* zig-zag (left-left) */
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = left_rotate(root->left);
        }
        return (root->left == NULL)? root: right_rotate(root);
    } else { 
        if (root->right == NULL) 
            return root;
        if (root->right->key > key) {     /* zag-zig (right-left)*/
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = right_rotate(root->right);
        } else if (root->right->key < key) {     /* zag-zag (right-right) */
            root->right->right = splay(root->right->right, key);
            root = left_rotate(root);
        }
        /* segunda rotacao para raiz */
        return (root->right == NULL)? root: left_rotate(root);
    }
}

struct Node *splay_remove(struct Node *root, int key) {

    if (!root)
        return NULL;

    struct Node *node = splay_search(root, key);
    if (!node || node->key != key)
        return node;

    if (!node->left && !node->right) {           /* caso não tenha filhos */
        free(node);
        return NULL;
    } else if (!node->left || !node->right) {    /* caso tenha 1 filho */
        struct Node* temp = node->left ? node->left : node->right;
        *node = *temp;
        free(temp);
    } else {                                     /* caso tenha 2 filhos */
        struct Node* predecessor = max_node(node->left);
        node->key = predecessor->key;
        node->left = splay_remove(node->left, predecessor->key);
    }

    return node;
}

int main() {

    struct Node *root = NULL;
    char op;
    int key;

    while (scanf("%c %d", &op, &key) == 2) {

        if (op == 'i')
            root = splay_insert(root, key);
        else 
        if (op == 'r')
            root = splay_remove(root, key);
        getchar(); /* '/n' */
    }
    
    inorder_print(root, 0);    
    free_tree(root);

    return 0;
}

struct Node {
    int tam;
    int c[3];
    struct Node *p[4];
};

int height(struct Node *root) {

    if (!root)
        return 0;
    return 1 + height(root->p[0]);
}