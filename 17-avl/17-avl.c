#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node *createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getHeight(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}
int getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + getHeight(y->left) > getHeight(y->right) 
                ? getHeight(y->left) : getHeight(y->right);
    x->height = 1 + getHeight(x->left) > getHeight(x->right) 
                ? getHeight(x->left) : getHeight(x->right);

    return x;
}

Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + getHeight(x->left) > getHeight(x->right) 
                ? getHeight(x->left) : getHeight(x->right);
    y->height = 1 + getHeight(y->left) > getHeight(y->right) 
                ? getHeight(y->left) : getHeight(y->right);

    return y;
}

Node *insert(Node *root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
    root->height = 1 + getHeight(root->left) > getHeight(root->right) 
                   ? getHeight(root->left) : getHeight(root->right);

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key) {
        return rotateRight(root);
    }
    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root);
    }
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

void printTree(Node *root) {
    if (root == NULL) {
        return;
    }
    printTree(root->left);
    printf("%d ", root->key);
    printTree(root->right);
}

