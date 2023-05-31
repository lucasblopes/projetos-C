#include <stdio.h>
#include <stdlib.h>
#include "generic.h"

struct Node {

    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int height;
    void *key; /* tipo generico */
    void (*print)(void *); /* imprime um dado generico */
    int (*cmp)(void *, void *); /* compara dois dados genericos */
};

enum type {CHAR, INT, FLOAT, DOUBLE};

/* aloca memoria para um novo nodo */
struct Node *new_node(void *key, void (*print_func) (void *), int (*cmp_func) (void *, void *)) {

    struct Node *node = malloc(sizeof(struct Node));
    if (!node) {
        perror("Error on malloc!\n");
        exit(1);
    }

    node->key = key;
    node->height = 0;
    node->parent = NULL;
    node->right = NULL;
    node->left = NULL;
    node->print = print_func;
    node->cmp = cmp_func;
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
        node->print(node->key);
        printf(",%d\n", level);
        inorder_print(node->right, level + 1);
    }
}

/* calcula a altura de um nodo */
int height(struct Node *p) {

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
struct Node *max_node(struct Node *node) {

    if (node->right == NULL)
        return node;
    else
        return max_node(node->right);
}

/* rotacao esquerda de uma sub-arvore */
struct Node *left_rotation(struct Node *p) {

    struct Node* q = p->right;

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
struct Node *right_rotation(struct Node *p) {

    struct Node *q = p->left;

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
int balance_factor(struct Node* p) {

    if (!p)
        return 0;

    return (height(p->left) - height(p->right));
}

/* realiza o balancemento de uma arvore avl cobrindo todos os casos de rotacoes */
struct Node *tree_balance(struct Node* node) {

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
struct Node *node_insert(struct Node *root, struct Node *node) {

    if (!root)
        return node;
    if (node->cmp(node->key, root->key) < 0) {
        root->left = node_insert(root->left, node);
        root->left->parent = root; 
    } else 
    if (node->cmp(node->key, root->key) > 0) { /* sem repeticao de nodo */
        root->right = node_insert(root->right, node);
        root->right->parent = root;
    }

    root->height = height(root);
    root = tree_balance(root);

    return root; 
}

/* remove um nodo da arvore avl e realiza o balancemanto, se necessario */
struct Node *node_remove(struct Node* node, void *key) {

    if (!node)
        return NULL;

    if (node->cmp(node->key, key) == 0) {
        if (!node->left && !node->right) {          /* caso nao tenha filhos */
            free(node);
            return NULL;
       } else if (!node->left || !node->right) {    /* caso tenha 1 filho */
            struct Node* temp = node->left ? node->left : node->right;
            *node = *temp;
            free(temp);
        } else {                                    /* caso tenha 2 filhos */
            struct Node* anteccessor = max_node(node->left);
            node->key = anteccessor->key;
            node->left = node_remove(node->left, anteccessor->key);
        }
    } else { /* busca binaria do nodo */
        if (node->cmp(key, node->key) < 0)
            node->left = node_remove(node->left, key);
        else
            node->right = node_remove(node->right, key);
    }

    if (!node)
        return NULL;

    node->height = height(node);
    node = tree_balance(node);

    return node;
}

int main() {

    struct Node *root = NULL;
    enum type var;
    char op;

    printf("escolha o tipo da variavel da chave:\n");
    printf("[0]char\n[1]int\n[2]float[3]double\n[4]string\n");
    scanf("%d", (int*)&var);

    if (var == CHAR) {
        char key;
        while (scanf("%c %c", &op, &key) != EOF) {
            if (op == 'i')
                root = node_insert(root, new_node(&key, char_print, char_cmp));
            else 
            if (op == 'r')
                root = node_remove(root, &key);
            getchar(); /* '/n' */
        }
    } else if (var == INT) {
        int key;
        while (scanf("%c %d", &op, &key) != EOF) {
            if (op == 'i')
                root = node_insert(root, new_node(&key, int_print, int_cmp));
            else 
            if (op == 'r')
                root = node_remove(root, &key);
            getchar(); /* '/n' */
        }  
    } else if (var == FLOAT) {
        float key;
        while (scanf("%c %f", &op, &key) != EOF) {
            if (op == 'i')
                root = node_insert(root, new_node(&key, float_print, float_cmp));
            else 
            if (op == 'r')
                root = node_remove(root, &key);
            getchar(); /* '/n' */
        }
    } else if (var == DOUBLE) {
        double key;
        while (scanf("%c %lf", &op, &key) != EOF) {
            if (op == 'i')
                root = node_insert(root, new_node(&key, double_print, double_cmp));
            else 
            if (op == 'r')
                root = node_remove(root, &key);
            getchar(); /* '/n' */
        }
         
    }
    inorder_print(root, 0);  
    free_tree(root);

    return 0;
}