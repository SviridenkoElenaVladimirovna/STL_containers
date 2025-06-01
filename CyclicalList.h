/*
Sviridenko Elena st130482@student.spbu.ru
A template container that implements a STL-style.
It supports iterators, standard concepts, error handling, and standard operators
*/
#ifndef CYCLICALLIST_H
#define CYCLICALLIST_H
/**
 * @file CyclicalList.h
 * @brief Implementation of an STL-style cyclic double-linked list.
 *
 * a template container that implements an STL-style
 *
 *It supports iterators, standard concepts, error handling, and standard operators
 */

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <concepts>
#include <utility>
/**
 * @class CyclicalList
 * @brief A cyclic bilinked list with an STL container interface.
 *
 * Stores elements of type `T` as a cyclic doubly-linked structure.
 * Supports insertion at start and end, deletion, iterators, and relocation.
 *
 * @tparam T The type of elements stored in the list. Must be copyable and destructible.
 */
template <typename T>
requires std::copy_constructible<T> && std::destructible<T>
class CyclicalList {
private:
    /**
    * @struct Node
    * @brief List Node. Stores data and pointers to next/previous nodes.
    */
    struct Node {
        T data;
        Node* next;
        Node* prev;

        explicit Node(const T& value) : data(value), next(this), prev(this) {}
        explicit Node(T&& value) : data(std::move(value)), next(this), prev(this) {}
    };

    Node* head = nullptr;
    size_t count = 0;
    /**
     * @brief Checks that the list is not empty.
     * @throws std::out_of_range if the list is empty.
     */
    void check_not_empty() const {
        if (empty()) {
            throw std::out_of_range("CyclicalList: operation on empty list");
        }
    }

public:
    CyclicalList() noexcept = default;

    CyclicalList(const CyclicalList& other) {
        for (const T& val : other) {
            push_back(val);
        }
    }

    CyclicalList(CyclicalList&& other) noexcept
            : head(other.head), count(other.count) {
        other.head = nullptr;
        other.count = 0;
    }

    CyclicalList& operator=(const CyclicalList& other) {
        if (this != &other) {
            CyclicalList temp(other);
            swap(temp);
        }
        return *this;
    }

    CyclicalList& operator=(CyclicalList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            count = other.count;
            other.head = nullptr;
            other.count = 0;
        }
        return *this;
    }

    ~CyclicalList() {
        clear();
    }
    /**
       * @class iterator
       * @brief Bidirectional iterator on list elements.
       *
       * Allows to move forward and backward through the list.
       * Compatible with STL algorithms.
       */
    class iterator {
        friend class CyclicalList;

        Node* node = nullptr;
        const Node* head = nullptr;

        explicit iterator(Node* n, const Node* h) : node(n), head(h) {}

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() = default;

        reference operator*() const {
            if (!node) throw std::out_of_range("Dereferencing end() iterator");
            return node->data;
        }

        pointer operator->() const {
            return std::addressof(operator*());
        }

        iterator& operator++() {
            if (!node) throw std::out_of_range("Incrementing end() iterator");
            node = (node->next == head) ? nullptr : node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            if (!head) throw std::out_of_range("Decrementing iterator in empty list");
            if (!node) node = const_cast<Node*>(head->prev);
            else node = node->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const noexcept {
            return node == other.node;
        }

        bool operator!=(const iterator& other) const noexcept {
            return node != other.node;
        }
    };

    using const_iterator = iterator;

    iterator begin() noexcept {
        return iterator(head, head);
    }

    iterator end() noexcept {
        return iterator(nullptr, head);
    }

    const_iterator begin() const noexcept {
        return const_iterator(head, head);
    }

    const_iterator end() const noexcept {
        return const_iterator(nullptr, head);
    }

    bool empty() const noexcept {
        return count == 0;
    }

    size_t size() const noexcept {
        return count;
    }

    T& front() {
        check_not_empty();
        return head->data;
    }

    const T& front() const {
        check_not_empty();
        return head->data;
    }

    T& back() {
        check_not_empty();
        return head->prev->data;
    }

    const T& back() const {
        check_not_empty();
        return head->prev->data;
    }

    void push_back(const T& value) {
        Node* node = new Node(value);
        if (!head) {
            head = node;
        } else {
            Node* tail = head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
        }
        ++count;
    }

    void push_back(T&& value) {
        Node* node = new Node(std::move(value));
        if (!head) {
            head = node;
        } else {
            Node* tail = head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
        }
        ++count;
    }

    void push_front(const T& value) {
        push_back(value);
        head = head->prev;
    }

    void push_front(T&& value) {
        push_back(std::move(value));
        head = head->prev;
    }

    void pop_back() {
        check_not_empty();
        Node* tail = head->prev;
        if (tail == head) {
            delete tail;
            head = nullptr;
        } else {
            tail->prev->next = head;
            head->prev = tail->prev;
            delete tail;
        }
        --count;
    }

    void pop_front() {
        check_not_empty();
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node* old_head = head;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
            delete old_head;
        }
        --count;
    }

    iterator insert(iterator pos, const T& value) {
        if (pos.node == nullptr || head == nullptr) {
            push_back(value);
            return iterator(head->prev, head);
        }
        Node* cur = pos.node;
        Node* prev = cur->prev;
        Node* node = new Node(value);
        node->next = cur;
        node->prev = prev;
        prev->next = node;
        cur->prev = node;
        if (cur == head) head = node;
        ++count;
        return iterator(node, head);
    }

    iterator insert(iterator pos, T&& value) {
        if (pos.node == nullptr || head == nullptr) {
            push_back(std::move(value));
            return iterator(head->prev, head);
        }
        Node* cur = pos.node;
        Node* prev = cur->prev;
        Node* node = new Node(std::move(value));
        node->next = cur;
        node->prev = prev;
        prev->next = node;
        cur->prev = node;
        if (cur == head) head = node;
        ++count;
        return iterator(node, head);
    }

    iterator erase(iterator pos) {
        if (empty())
            throw std::out_of_range("erase on empty list");
        if (pos.node == nullptr)
            throw std::out_of_range("erase called with end() iterator");

        Node* node = pos.node;
        iterator iter(node->next == head ? nullptr : node->next, head);
        if (node->next == node) {
            delete node;
            head = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if (node == head) head = node->next;
            delete node;
        }
        --count;
        return iter;
    }


    void clear() noexcept {
        while (!empty()) {
            pop_front();
        }
    }

    void assign(size_t n, const T& value) {
        clear();
        for (size_t i = 0; i < n; ++i) {
            push_back(value);
        }
    }

    void swap(CyclicalList& other) noexcept {
        std::swap(head, other.head);
        std::swap(count, other.count);
    }
    bool operator==(const CyclicalList& other) const {
        if (count != other.count) return false;
        auto it1 = begin();
        auto it2 = other.begin();
        while (it1 != end() && it2 != other.end()) {
            if (*it1 != *it2) return false;
            ++it1;
            ++it2;
        }
        return true;
    }

    bool operator!=(const CyclicalList& other) const {
        return !(*this == other);
    }


};

/**
 * @brief Exchanges the contents of two lists.
 * @tparam T The type of items in the list.
 * @param lhs First list.
 * @param rhs Second list.
 */
template <typename T>
void swap(CyclicalList<T>& lhs, CyclicalList<T>& rhs) noexcept {
    lhs.swap(rhs);
}

#endif
