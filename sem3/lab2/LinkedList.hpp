#pragma once

#include "Collection.hpp"

template <class T> class LinkedList : public Collection<T> {

public:

    class Node {
    public:
        T item;
        Node *next;
        Node(T item) : item(item), next(nullptr) {};

        T operator*() {
            return this->item;
        }
    };

    LinkedList() : first(nullptr), last(nullptr) {};

    LinkedList(T *items, int count) : LinkedList() {
        if (count == 0)
            return;
        
        this->size = count;

        for (int i = 0; i < count; i++) {
            this->Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &input_list) : LinkedList() {
        for (auto i : input_list) {
            this->Append(i);
        }
    }

    void swap(int i, int j) {
        if (i >= this->size || j >= this->size || i < 0 || j < 0) {
            throw std::out_of_range("Index out of range");
        }
        Node *current_i = this->first;
        Node *current_j = this->first;
        for (int k = 0; k < i; k++) {
            current_i = current_i->next;
        }
        for (int k = 0; k < j; k++) {
            current_j = current_j->next;
        }
        T tmp = current_i->item;
        current_i->item = current_j->item;
        current_j->item = tmp;
    }

    void Clear() {
        Node *current = this->first;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
    }


    T Get(int index) const override {
        if (index >= this->size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        Node *current = this->first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->item;
    }

    LinkedList<T> *GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= this->size || startIndex > endIndex) {
            throw std::out_of_range("Index out of range");
        }
        LinkedList<T> *result = new LinkedList<T>();
        Node *current = this->first;
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
        }
        for (int i = startIndex; i <= endIndex; i++) {
            result->Append(current->item);
            current = current->next;
        }
        return result;
    }

    int GetLength() const override {
        return this->size;
    }

    void Append(T item) {
        Node *new_node = new Node(item);
        if (this->first == nullptr) {
            this->first = new_node;
            this->last = new_node;
        } else {
            this->last->next = new_node;
            this->last = new_node;
        }
        this->size++;
    }

    LinkedList<T> *Append(T item) const {
        LinkedList<T> *result = new LinkedList<T>(*this);
        result->Append(item);
        return result;
    }

    void Prepend(T item) {
        Node *new_node = new Node(item);
        if (this->first == nullptr) {
            this->first = new_node;
            this->last = new_node;
        } else {
            new_node->next = this->first;
            this->first = new_node;
        }
        this->size++;
    }

    LinkedList<T> *Prepend(T item) const {
        LinkedList<T> *result = new LinkedList<T>(*this);
        result->Prepend(item);
        return result;
    }

    void InsertAt(T item, int index) {
        if (index >= this->size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        Node *new_node = new Node(item);
        if (index == 0) {
            if (this->first == nullptr) {
            this->first = new_node;
            this->last = new_node;
            } else {
                new_node->next = this->first;
                this->first = new_node;
            }
        } else {
            Node *current = this->first;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
        this->size++;
    }

    LinkedList<T> *InsertAt(T item, int index) const {
        LinkedList<T> *result = new LinkedList<T>(*this);
        result->InsertAt(item, index);
        return result;
    }

    LinkedList<T> *Concat(const LinkedList<T> &input_list) const {
        LinkedList<T> *result = new LinkedList<T>(*this);
        for (auto i : input_list) {
            result->Append(i);
        }
        return result;
    }

    T& operator[](int index) {
        return this->GetLinkedListItem(index);
    }

    const T operator[](int index) const {
        return this->Get(index);
    }

    ~LinkedList() {
        Node *current = this->first;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
    }
    class Iterator {
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = Node*;
	using reference = value_type&;

	pointer ptr;

    public:

        Iterator(pointer ptr) {
            this->ptr = ptr;
        }

        Iterator &operator++() {
            this->ptr = this->ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            this->ptr = this->ptr->next;
            return tmp;
        }

        bool operator==(const Iterator &other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const Iterator &other) const {
            return this->ptr != other.ptr;
        }
    
        reference operator*() {
            return ptr->item;
        }

        pointer operator->() {
            return ptr;
        }
    };

    class ConstIterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = Node*;
        using reference = value_type&;

        pointer ptr;

    public:
            
            ConstIterator(pointer ptr) {
                this->ptr = ptr;
            }
    
            ConstIterator &operator++() {
                this->ptr = this->ptr->next;
                return *this;
            }
    
            ConstIterator operator++(int) {
                ConstIterator tmp = *this;
                this->ptr = this->ptr->next;
                return tmp;
            }
    
            bool operator==(const ConstIterator &other) const {
                return this->ptr == other.ptr;
            }
    
            bool operator!=(const ConstIterator &other) const {
                return this->ptr != other.ptr;
            }
    
            const T& operator*() {
                return ptr->item;
            }
    
            const Node *operator->() {
                return ptr;
            }
        };


    Iterator begin() {
        return Iterator(this->first);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    ConstIterator begin() const {
        return ConstIterator(this->first);
    }

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }


private:
    Node *first;
    Node *last;
    int size = 0;

protected:
    T& GetLinkedListItem(int index) {
        Node *current = this->first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->item;
    }

};



