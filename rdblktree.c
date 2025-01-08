#include <stdio.h>
#include <stdlib.h>

// Define the color for the nodes
#define RED 0
#define BLACK 1

// Red-Black Tree Node structure
struct RBNode {
    int data;
    int color;  // RED or BLACK
    struct RBNode *left, *right, *parent;
};

// Root of the Red-Black Tree
struct RBNode *root = NULL;

// Function to create a new Red-Black tree node
struct RBNode* createNode(int data) {
    struct RBNode *newNode = (struct RBNode*)malloc(sizeof(struct RBNode));
    newNode->data = data;
    newNode->color = RED;  // New node is always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Left rotate the subtree rooted at node
void leftRotate(struct RBNode **root, struct RBNode *x) {
    struct RBNode *y = x->right;
    x->right = y->left;

    if (y->left != NULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Right rotate the subtree rooted at node
void rightRotate(struct RBNode **root, struct RBNode *y) {
    struct RBNode *x = y->left;
    y->left = x->right;

    if (x->right != NULL) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// Fix the Red-Black Tree after insertion
void fixViolation(struct RBNode **root, struct RBNode *pt) {
    struct RBNode *parent_pt = NULL;
    struct RBNode *grandparent_pt = NULL;

    while (pt != *root && pt->color == RED && pt->parent->color == RED) {
        parent_pt = pt->parent;
        grandparent_pt = pt->parent->parent;

        // Case 1: Parent is the left child of grandparent
        if (parent_pt == grandparent_pt->left) {
            struct RBNode *uncle = grandparent_pt->right;

            // Case 1a: Uncle is RED
            if (uncle != NULL && uncle->color == RED) {
                grandparent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle->color = BLACK;
                pt = grandparent_pt;  // Move up the tree
            } else {
                // Case 1b: Uncle is BLACK and pt is the right child
                if (pt == parent_pt->right) {
                    leftRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                // Case 1c: Uncle is BLACK and pt is the left child
                rightRotate(root, grandparent_pt);
                parent_pt->color = BLACK;
                grandparent_pt->color = RED;
                pt = parent_pt;
            }
        } else {  // Case 2: Parent is the right child of grandparent
            struct RBNode *uncle = grandparent_pt->left;

            // Case 2a: Uncle is RED
            if (uncle != NULL && uncle->color == RED) {
                grandparent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle->color = BLACK;
                pt = grandparent_pt;
            } else {
                // Case 2b: Uncle is BLACK and pt is the left child
                if (pt == parent_pt->left) {
                    rightRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                // Case 2c: Uncle is BLACK and pt is the right child
                leftRotate(root, grandparent_pt);
                parent_pt->color = BLACK;
                grandparent_pt->color = RED;
                pt = parent_pt;
            }
        }
    }

    (*root)->color = BLACK;  // Root must always be black
}

// Insert a node into the Red-Black Tree
void insert(struct RBNode **root, int data) {
    struct RBNode *newNode = createNode(data);

    // Standard Binary Search Tree Insert
    if (*root == NULL) {
        *root = newNode;
        newNode->color = BLACK;  // Root is always black
        return;
    }

    struct RBNode *temp = *root;
    struct RBNode *parent = NULL;

    while (temp != NULL) {
        parent = temp;
        if (data < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    newNode->parent = parent;
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Fix violations of Red-Black Tree properties
    fixViolation(root, newNode);
}

// Inorder traversal of the Red-Black Tree
void inorder(struct RBNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d (%s) ", root->data, root->color == RED ? "RED" : "BLACK");
        inorder(root->right);
    }
}

// Main function to test the Red-Black Tree insertion
int main() {
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);

    printf("Inorder Traversal of the Red-Black Tree:\n");
    inorder(root);
    printf("\n");

    return 0;
}

