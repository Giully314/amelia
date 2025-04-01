// amelia/ds/rb_tree.h
// PURPOSE: Define a red-black tree.
//
// STRUCTS:
//
//
// DESCRIPTION:
//
// 

#ifndef _AMELIA_DS_RB_TREE_H
#define _AMELIA_DS_RB_TREE_H

#include <amelia/basic_types.h>
#include <amelia/memory/pool_allocator.h>

typedef enum RBColor : u8 {
    RB_RED,
    RB_BLACK,
} RBColor_e;

typedef struct RBNode {
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
    void *data;
    i32 key;
    enum RBColor color;
} RBNode_t;

#define RB_EMPTY_NODE {.parent=nullptr, .left=nullptr, .right=nullptr\
    .data=nullptr, .key=-1, .color=RB_RED}

typedef struct RBTree {
    struct RBNode *root;

    // number of elements.
    u64 size;

    // Return -1 if akey <= bkey, 1 if akey > bkey.
    i32 (*cmp)(i32 akey, i32 bkey);

    // Free the memory of the data.
    void (*free)(void *data);

    struct PoolAllocator *a;
} RBTree_t;

#define RB_EMPTY_TREE {.root=RB_EMPTY_NODE, .size=0, .cmp=nullptr, .free=nullptr,\
    .a=nullptr}

// Insert data in the tree.
void rb_tree_insert(struct RBTree *tree, const i32 key, void *data);

// Delete a node with key. Do nothing if there is no such node.
void rb_tree_delete(struct RBTree *tree, void* key);

// Free the tree.
void rb_tree_free();

// Return the data associated to the key if present, NULL otherwise.
void* rb_tree_find(const struct RBTree tree, void *key);

// Return the data of the min node.
void* rb_tree_min(const struct RBTree tree);

// Return the data of the max node.
void* rb_tree_max(const struct RBTree tree);

#endif // _AMELIA_DS_RB_TREE_H