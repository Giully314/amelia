// src/ds/dl_list.c
#include <amelia/ds/dl_list.h>

static struct DLNode *create_node(struct DLList *list, void *data)
{
	struct DLNode *node = (struct DLNode *)pool_allocator_get(list->alloc);
	node->data = data;
	node->prev = nullptr;
	node->next = nullptr;

	return node;
}

static void delete_node(struct DLList *list, struct DLNode *node)
{
	if (node->prev != nullptr) {
		node->prev->next = node->next;
	}
	if (node->next != nullptr) {
		node->next->prev = node->prev;
	}

	pool_allocator_release(list->alloc, (void *)node);
}

void dl_list_push_back(struct DLList *list, void *data)
{
	struct DLNode *node_to_insert = create_node(list, data);
	if (list->last == nullptr) {
		list->first = node_to_insert;
		list->last = node_to_insert;
	} else {
		list->last->next = node_to_insert;
		node_to_insert->prev = list->last;
		list->last = node_to_insert;
	}
	++list->size;
}

void dl_list_push_front(struct DLList *list, void *data)
{
	struct DLNode *node_to_insert = create_node(list, data);
	if (list->first == nullptr) {
		list->first = node_to_insert;
		list->last = node_to_insert;
	} else {
		list->first->prev = node_to_insert;
		node_to_insert->next = list->next;
		list->first = node_to_insert;
	}
	++list->size;
}

void *dl_list_pop_back(struct DLList *list)
{
	if (list->last == nullptr) {
		return nullptr;
	}

	void *data = list->last->data;
	delete_node(list, list->last);

	return data;
}

void *dl_list_pop_front(struct DLList *list)
{
	if (list->first == nullptr) {
		return nullptr;
	}

	void *data = list->first->data;
	delete_node(list, list->first);

	return data;
}