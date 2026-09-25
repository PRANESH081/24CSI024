#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int height;
    struct Node *left, *right;
};

int height(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int balance(struct Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

struct Node* insert(struct Node *node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int b = balance(node);

    if (b > 1 && key < node->left->key)
        return rightRotate(node);

    if (b < -1 && key > node->right->key)
        return leftRotate(node);

    if (b > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (b < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int main() {
    struct Node *root = NULL;
    int key;

    while (scanf("%d", &key) == 1 && key != -1) {
        root = insert(root, key);
    }

    printf("Height of the AVL tree: %d", height(root));

    return 0;
}