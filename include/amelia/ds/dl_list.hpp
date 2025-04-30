// amelia/ds/dl_list.hpp
// PURPOSE: Define a double linked list.
//
// CLASSES:
//
// DESCRIPTION:
//

#pragma once

#include <amelia/memory/block.hpp>
#include <amelia/memory/memory_concepts.hpp>
#include <amelia/memory/memory_utils.hpp>
#include <amelia/types.hpp>

namespace amelia {

// TODO: T should be regular.
template<typename T>
struct DLNode {
    DLNode() = default;

    DLNode(const DLNode &) = delete;
    DLNode &operator=(const DLNode &) = delete;

    DLNode(DLNode &&) = default;
    DLNode &operator=(DLNode &&) = default;

    DLNode(DLNode *prev_, DLNode *next_, const T &data_): prev{prev_}, next{next_}, data{data_} {}

    DLNode *prev{nullptr};
    DLNode *next{nullptr};
    T data;
};

// TODO: T should be regular.
template<typename T, RawAllocator TAlloc>
class DLList {
public:
    using node_type = DLNode<T>;

    DLList(TAlloc &alloc_): alloc(alloc_) {}

    ~DLList() {
        // free memory.
    }

    auto push_back(const T &data) -> void {
        MemoryBlock block = alloc.allocate(sizeof(node_type));

        construct_at<node_type>(block.data);
        node_type *node = static_cast<node_type>(block.data);

        node->data = data;

        if(!root) {
            root = node;
            last = node;
        } else {
            last->next = node;
            node->prev = last;
            last = node;
        }
    }

    // auto push_front() -> void;

    constexpr auto size() const -> u64 {
        return msize;
    }

private:
    DLNode<T> *root{nullptr};
    DLNode<T> *last{nullptr};

    u64 msize{0};

    TAlloc &alloc;
};

} // namespace amelia
