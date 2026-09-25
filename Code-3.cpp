#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data, height;
    struct Node *left, *right;
};

int height(struct Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct Node* newNode(int data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;
    x->right = y;
    y->left = t;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;
    y->left = x;
    x->right = t;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int balance(struct Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

struct Node* insert(struct Node *root, int data) {
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && data < root->left->data)
        return rightRotate(root);

    if (b < -1 && data >= root->right->data)
        return leftRotate(root);

    if (b > 1 && data >= root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int countGreater(struct Node *root, int x) {
    if (root == NULL)
        return 0;

    if (root->data > x)
        return 1 + countGreater(root->left, x) + countGreater(root->right, x);

    return countGreater(root->right, x);
}

int main() {
    int n, x, value;
    struct Node *root = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    scanf("%d", &x);

    printf("Number of elements greater than %d are %d", x, countGreater(root, x));

    return 0;
}