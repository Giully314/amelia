// src/ds/rb_tree.c
// IMPLEMENTATION:
//  For more details about the implementation see:
//  Introduction to algorithms chapter on Red-black trees.
//  https://github.com/zarif98sjs/RedBlackTree-An-Intuitive-Approach
//  The implementation used here is from Introduction to Algorithms.
//  The 5 properties that a RB tree must have at any time are:
//  1) Each node is either red or black;
//  2) root is black;
//  3) Every leaf (null) is black;
//  4) if a node is red, both its children are black;
//  5) for each node, all simple paths from the node to leaves contain the
//      same number of black nodes.
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

// This procedure fix the tree by checking if each property of the RB tree holds.
// The only properties that can be violated during an insertion are 2) and 4).
static void insert_fixup(struct RBTree* tree, struct RBNode* node) {
    // Check for violation of property 4.
    while (node->parent->color == RB_RED) {
        // Check if parent is a left child.
        if (node->parent == node->parent->parent->left) {
            struct RBNode* y = node->parent->parent->right;
            if (y->color == RB_RED) { // both parent and uncle are red
                // Change the color of arent and uncle (a red node can have only black children).
                node->parent->color = RB_BLACK;
                y->color = RB_BLACK;
                node->parent->parent->color = RB_RED;
                node = node->parent->parent;
            } else { // The uncle is black
                // Perform a left rotation is the node is a right child.
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(tree, node);
                }
                node->parent->color = RB_BLACK;
                node->parent->parent->color = RB_RED;
                right_rotate(tree, node->parent->parent);
            }
        } else { // Same as the if block but with right and left inverted.
            struct RBNode* y = node->parent->parent->left;
            if (y->color == RB_RED) { // both parent and uncle are red
                // Change the color of arent and uncle (a red node can have only black children).
                node->parent->color = RB_BLACK;
                y->color = RB_BLACK;
                node->parent->parent->color = RB_RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(tree, node);
                }
                node->parent->color = RB_BLACK;
                node->parent->parent->color = RB_RED;
                left_rotate(tree, node->parent->parent);
            }
        }
    }
    // Fix property 2;
    tree->root->color = RB_BLACK;
}

static struct RBNode* create_node(struct RBTree *tree, const rb_key_t key, void *data) {
    struct RBNode* node = (struct RBNode*)pool_allocator_get(tree->alloc);
    node->data = data;
    node->key = key;
    node->parent = nullptr;
    node->right = nullptr;
    node->left = nullptr;
    node->color = RB_RED;

    return node;
}

void rb_tree_insert(struct RBTree *tree, const rb_key_t key, void *data) {
    struct RBNode *x = tree->root;
    struct RBNode *y = nullptr;
    struct RBNode *node_to_insert = create_node(tree, key, data);
    
    while (x != nullptr) {
        y = x;
        if (tree->cmp(node_to_insert->key, x->key)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    node_to_insert->parent = y;
    if (y == nullptr) {
        tree->root = node_to_insert;
    } else if (tree->cmp(node_to_insert->key, y->key)) {
        y->left = node_to_insert;
    } else {
        y->right = node_to_insert;
    }
    
    insert_fixup(tree, node_to_insert);
    tree->size += 1;
}


static void transplant(struct RBTree* tree, struct RBNode* u, struct RBNode* v) {
    if (u->parent == nullptr) {
        tree->root = u;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

static struct RBNode* tree_min(struct RBNode *node) {
    struct RBNode *found = nullptr;
    while (node != nullptr) {
        found = node;
        node = node->left;
    }
    return found;
}

// Internal utility find, return a node.
static struct RBNode* find(const struct RBTree *tree, const rb_key_t key) {
    struct RBNode* x = tree->root;
    struct RBNode* y = nullptr;
    while (x != nullptr) {
        y = x;
        if (tree->cmp(x->key, key)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return y;
}

static void delete_fixup(struct RBTree *tree, struct RBNode *x) {
    while (x != tree->root && x->color == RB_BLACK) {
        if (x == x->parent->left) { 
            struct RBNode *w = x->parent->right;
            if (w->color == RB_RED) {
                w->color = RB_BLACK;
                x->parent->color = RB_RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RB_BLACK && w->right->color == RB_BLACK) {
                w->color = RB_RED;
                x = x->parent;
            } else {
                if (w->right->color == RB_BLACK) {
                    w->left->color = RB_BLACK;
                    w->color = RB_RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = RB_BLACK;
                w->right->color = RB_BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            struct RBNode *w = x->parent->left;
            if (w->color == RB_RED) {
                w->color = RB_BLACK;
                x->parent->color = RB_RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == RB_BLACK && w->left->color == RB_BLACK) {
                w->color = RB_RED;
                x = x->parent;
            } else {
                if (w->left->color == RB_BLACK) {
                    w->right->color = RB_BLACK;
                    w->color = RB_RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = RB_BLACK;
                w->left->color = RB_BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = RB_BLACK;
}

void rb_tree_delete(struct RBTree *tree, const rb_key_t key) {
    struct RBNode *z = find(tree, key);
    if (z == nullptr) {
        return;
    }

    struct RBNode *y = z;
    enum RBColor y_orig_color = y->color;
    struct RBNode *x = nullptr;

    if (z->left == nullptr) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = tree_min(z->right);
        y_orig_color= y->color;
        x = y->right;
        if (y != z->right) {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        } else {
            x->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_orig_color == RB_BLACK) {
        delete_fixup(tree, x);
    }

    // Free memory of z.
    tree->free(z->data);
    pool_allocator_release(tree->alloc, (void*)z);
    tree->size -= 1;
}


void* rb_tree_find(const struct RBTree *tree, const rb_key_t key) {
    struct RBNode* node = find(tree, key);
    if (node != nullptr) {
        return node->data;
    }
    return nullptr;
}


void* rb_tree_min(const struct RBTree *tree) {
    if (tree->root == nullptr) {
        return nullptr;
    }
    
    struct RBNode *m = tree_min(tree->root);
    return m->data;
}