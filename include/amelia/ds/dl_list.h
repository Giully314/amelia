// amelia/ds/dl_list.h
// PURPOSE: Define API for a double linked list.
//
// STRUCTS:
//  DLNode: the node of the double linked list.
//
// DESCRIPTION:
//

#ifndef _AMELIA_DS_DL_LIST_H
#define _AMELIA_DS_DL_LIST_H

#include <amelia/basic_types.h>
#include <amelia/memory/pool_allocator.h>

typedef struct DLNode {
	struct DLNode *next;
	struct DLNode *prev;
	void *data;
} DLNode_t;

#define DL_NODE_EMPTY { .next = nullptr, .prev = nullptr, .data = nullptr }

typedef struct DLList {
	struct DLNode *first;
	struct DLNode *last;

	u64 size;

	struct PoolAllocator *alloc;
} DLList_t;

#define DL_LIST_EMPTY { .first = nullptr, .last = nullptr, .size = 0 }

void dl_list_push_back(struct DLList *list, void *data);
void dl_list_push_front(struct DLList *list, void *data);

// Remove a node from the end and return data.
// Return nullptr if the list is empty.
void *dl_list_pop_back(struct DLList *list);

// Remove a node from the front and return data.
// Return nullptr if the list is empty.
void *dl_list_pop_front(struct DLList *list);

#endif // _AMELIA_DS_DL_LIST_H