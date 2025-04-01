// src/ds/rb_tree.c
// IMPLEMENTATION:
//  For more details about the implementation see:
//  Introduction to algorithms chapter on Red-black trees.
//  https://github.com/zarif98sjs/RedBlackTree-An-Intuitive-Approach
//  
#include <amelia/ds/rb_tree.h>


static void left_rotate(struct RBTree *tree, struct RBNode *node) {
    struct RBNode *y = node->right;
    node->right = y->left;
    
    if (y->left != nullptr) {
        y->left->parent = node;
    }
    
    y->parent = node->parent;
    if (y->parent == nullptr) {
        tree->root = y;
    } else if (node->parent->left == node) { // Check if node is left child.
        node->parent->left = y;
    } else { // node is right child.  
        node->parent->right = y;
    }
    
    node->parent = y;
    y->left = node;
}

static void right_rotate(struct RBTree *tree, struct RBNode *node) {
    struct RBNode *y = node->left;
    node->left = y->right;
    
    if (y->right != nullptr) {
        y->right->parent = node;
    }
    
    y->parent = node->parent;
    if (y->parent == nullptr) {
        tree->root = y;
    } else if (node->parent->left == node) { // Check if node is left child.
        node->parent->left = y;
    } else { // node is right child.  
        node->parent->right = y;
    }
    
    node->parent = y;
    y->right = node;
}


void rb_tree_insert(struct RBTree *tree, const i32 key, void *data) {
    // struct R
}
