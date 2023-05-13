#include <stdio.h>
#include <stdlib.h>

/* BST tree */
struct Node {

    struct Node *parent;
    struct Node *right;
    struct Node *left;
    int key;
};

struct Node *new_node(int key) {

    struct Node *n = malloc(sizeof(struct Node));
    if (!n) {
        perror("Error on malloc!\n");
        exit(1);
    }

    n->key = key;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void free_tree(struct Node *node) {

    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void inorder_walk(struct Node *node, int level) {

    if (node) {
        inorder_walk(node->left, level + 1);
        printf("%d,%d\n", node->key, level);
        inorder_walk(node->right, level + 1);
    }
}

int tree_size(struct Node *node) {

    if (node) {
        return tree_size(node->left) + tree_size(node->right) + 1;
    } else
        return 0;
}

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

struct Node *tree_minimum(struct Node *node) {

    if (node->left == NULL)
        return node;
    else
        return tree_minimum(node->left);
}

struct Node *tree_maximum(struct Node *node) {

    if (node->right == NULL)
        return node;
    else
        return tree_maximum(node->right);
}

/* binary search */
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

struct Node *left_rotate(struct Node *p) {

    struct Node* q = p->right;

    p->right = q->left;
    q->parent = p->parent;
    p->parent = q;

    if (q->left)
        q->left->parent = p;

    q->left = p;

    return q;
}

struct Node *right_rotate(struct Node *p) {

    struct Node *q = p->left;

    p->left = q->right;
    q->parent = p->parent;
    p->parent = q;

    if (q->right)
        q->right->parent = p;

    q->right = p;

    return q;
}

struct Node *root_insert(struct Node *node, int key) {

    if (!node)
        return new_node(key);
    if (key < node->key){
        node->left = root_insert(node->left, key);
        node->left->parent = node;
        node = right_rotate(node);
    }
    else {
        node->right = root_insert(node->right, key);
        node->right->parent = node;
        node = left_rotate(node);
    }
    return node;
}

struct Node *bst_insert(struct Node *node, int key) {

    if (!node)
        return new_node(key);
    if (key < node->key) {
        node->left = bst_insert(node->left, key);
        node->left->parent = node;
    }
    else {
        node->right = bst_insert(node->right, key);
        node->right->parent = node;
    }

    return node;
}

struct Node *transplant(struct Node *root, struct Node *node, struct Node *new) {

    if (!node->parent)
        return new; /* root = new */
    else if (node == node->parent->left)
        node->parent->left = new;
    else 
        node->parent->right = new;
    if (new)
        new->parent = node->parent;

    return root;
}
 
struct Node *bst_remove(struct Node* root, int key) {

    struct Node *node = tree_search(root, key);
    if (!node)
        return root;

    if (node->left == NULL) {
        root = transplant(root, node, node->right);
    } else {
        if (node->right == NULL) {
            root = transplant(root, node, node->left);
        }
        else {
            struct Node *s = tree_minimum(node->right); /* sucessor */
            if (s->parent != node) { 
                root = transplant(root, s, s->right);
                s->right = node->right;
                s->right->parent = s;
            }
            root = transplant(root, node, s);
            s->left = node->left;
            s->left->parent = s;
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
            root = bst_insert(root, key);
        else 
        if (op == 'r')
            root = bst_remove(root, key);
        getchar(); /* '/n' */
    }

    inorder_walk(root, 0);
    free_tree(root);

    return 0;
}
