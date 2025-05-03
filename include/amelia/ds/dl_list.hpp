// amelia/ds/dl_list.hpp
// PURPOSE: Define a double linked list.
//
// CLASSES:
//
// DESCRIPTION:
//
// TODO:
//  * Add concepts to the template types.

#pragma once

#include <amelia/concepts.hpp>
#include <amelia/memory/block.hpp>
#include <amelia/memory/memory_concepts.hpp>
#include <amelia/memory/memory_utils.hpp>
#include <amelia/types.hpp>

namespace amelia {

// TODO: T should be regular.
template<typename T>
struct DLNode {
    DLNode() = default;

    DLNode(DLNode* prev_, DLNode* next_, const T& data_): prev{prev_}, next{next_}, data{data_} {}

    DLNode* prev{nullptr};
    DLNode* next{nullptr};
    T data;
};

template<typename T>
class DLListIterator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    DLListIterator() {}

    DLListIterator(DLNode<T>* c): current{c} {}

    auto operator++() -> DLListIterator& {
        current = current->next;
        return *this;
    }

    auto operator++(int) -> DLListIterator {
        auto temp = *this;
        current = current->next;
        return temp;
    }

    auto operator--() -> DLListIterator& {
        current = current->prev;
        return *this;
    }

    auto operator--(int) -> DLListIterator {
        auto temp = *this;
        current->prev;
        return temp;
    }

    template<typename Self>
    constexpr auto&& operator*(this Self&& self) {
        return self.current->data;
    }

    template<typename Self>
    constexpr auto&& operator->(this Self&& self) {
        return &(self.current->data);
    }

    friend auto operator==(const DLListIterator& lhs, const DLListIterator& rhs) -> bool = default;

private:
    DLNode<T>* current{nullptr};
};

// TODO: T should be regular.
template<typename T, RawAllocator TAlloc>
class DLList {
public:
    using node_type = DLNode<T>;

    DLList(TAlloc& alloc_): alloc(alloc_) {}

    ~DLList() {
        // free memory.
    }

    auto push_back(const T& data) -> void {
        MemoryBlock block = alloc.allocate(sizeof(node_type));

        node_type* node = reinterpret_cast<node_type*>(block.data);
        *node = node_type{};
        node->data = data;

        if(!root) {
            root = node;
            last = node;
        } else {
            last->next = node;
            node->prev = last;
            last = node;
        }
        ++msize;
    }

    // auto push_front() -> void;

    constexpr auto size() const -> u64 {
        return msize;
    }

    constexpr auto begin() -> DLListIterator<T> {
        return DLListIterator<T>{root};
    }

    constexpr auto end() -> DLListIterator<T> {
        return DLListIterator<T>{nullptr};
    }

    constexpr auto cbegin() const -> DLListIterator<T> {
        return DLListIterator<T>{root};
    }

    constexpr auto cend() const -> DLListIterator<T> {
        return DLListIterator<T>{nullptr};
    }

private:
    DLNode<T>* root{nullptr};
    DLNode<T>* last{nullptr};

    u64 msize{0};

    TAlloc& alloc;
};

} // namespace amelia
