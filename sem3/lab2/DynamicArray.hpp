#pragma once

#include <iostream>

using namespace std;

#include "Collection.hpp"


template <class T> class DynamicArray : public Collection<T> {
    T *items;
    int size = 0;
    int capacity = 0;

public:
    DynamicArray(T *items, int count) : size(count), capacity(count * 2) {
        this->items = new T[this->capacity];
        for (int i = 0; i < count; i++) {
            this->items[i] = items[i];
        }
    };

    DynamicArray() : DynamicArray(0) {};

    DynamicArray(int size) : size(0), capacity(size * 2) {
        this->items = new T[this->capacity];
    };
    

    DynamicArray(const DynamicArray<T> &dynamicArray) : DynamicArray(dynamicArray.items, dynamicArray.size) {};

    void Clear() {
        this->size = 0;
        this->capacity = 0;
        delete[] items;
        items = new T[capacity];
    }
    
    T Get(int index) const {
        if (index >= this->size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        return this->items[index];
    }

    int GetLength() const {
        return this->size;
    }

    T GetFirst() const  {
        return this->items[0];
    }

    T GetLast() const {
        return this->items[this->size - 1];
    }

    void Set(int index, T value) {
        if (index >= this->size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        this->items[index] = value;
    }
    
    DynamicArray<T> *Set(int index, T value) const {
        DynamicArray<T> *copy = new DynamicArray<T>(*this);
        copy->Set(index, value);
        return copy;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("New size must be positive");
        }
        
        if (newSize > capacity) {
            capacity = newSize * 2;
            T *tmp = new T[capacity];

            for (int i = 0; i < size; i++) {
                tmp[i] = items[i];
            }

            delete[] items;
            items = tmp;
        }

        size = newSize;
    }

    DynamicArray<T> *Resize(int newSize) const {
        DynamicArray<T> *copy = new DynamicArray<T>(*this);
        copy->Resize(newSize);
        return copy;
    }

    void Append(T value) {
        if (this->size * 2 >= capacity) {
            capacity = (capacity == 0) ? 2 : capacity * 2;
            T *tmp = new T[capacity];

            for (int i = 0; i < size; i++) {
                tmp[i] = items[i];
            }

            delete[] items;
            items = tmp;
        }

        items[size] = value;
        this->size++;
    }

    DynamicArray<T> *Append(T value) const {
        DynamicArray<T> *copy = new DynamicArray<T>(*this);
        copy->Append(value);
        return copy;
    }

    void Prepend(T value) {
        if (this->size * 2 >= capacity) {
            capacity *= 2;
            T *tmp = new T[capacity];

            for (int i = 0; i < size; i++) {
                tmp[i] = items[i];
            }

            delete[] items;
            items = tmp;
        }

        for (int i = size; i > 0; i--) {
            items[i] = items[i - 1];
        }

        items[0] = value;
        this->size++;
    }

    DynamicArray<T> *Prepend(T value) const {
        DynamicArray<T> *copy = new DynamicArray<T>(*this);
        copy->Prepend(value);
        return copy;
    }

    void InsertAt(T value, int index) {
        if (index >= this->size || index < 0) {
            throw std::out_of_range("Index out of range");
        }

        if (this->size * 2 >= capacity) {
            capacity *= 2;
            T *tmp = new T[capacity];

            for (int i = 0; i < size; i++) {
                tmp[i] = items[i];
            }

            delete[] items;
            items = tmp;
        }

        for (int i = size; i > index; i--) {
            items[i] = items[i - 1];
        }

        items[index] = value;
        this->size++;
    }

    DynamicArray<T> *InsertAt(T value, int index) const {
        DynamicArray<T> *copy = new DynamicArray<T>(*this);
        copy->InsertAt(value, index);
        return copy;
    }

    DynamicArray<T> *GetSubArray(int startIndex, int endIndex) const {
        if (startIndex >= this->size || startIndex < 0) {
            throw std::out_of_range("Start index out of range");
        }

        if (endIndex >= this->size || endIndex < 0) {
            throw std::out_of_range("End index out of range");
        }

        if (startIndex > endIndex) {
            throw std::invalid_argument("Start index must be less than end index");
        }

        DynamicArray<T> *result = new DynamicArray<T>(endIndex - startIndex + 1);

        for (int i = startIndex; i <= endIndex; i++) {
            result->Append(this->items[i]);
        }

        return result;
    }

    T& operator[](int index) {
        if (index >= this->size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        return this->items[index];
    }

    const T operator[](int index) const {
        return Get(index);
    }

    void swap(int index1, int index2) {
        if (index1 >= this->size || index1 < 0) {
            throw std::out_of_range("Index1 out of range");
        }

        if (index2 >= this->size || index2 < 0) {
            throw std::out_of_range("Index2 out of range");
        }

        T tmp = this->items[index1];
        this->items[index1] = this->items[index2];
        this->items[index2] = tmp;
    }

    ~DynamicArray() {
        delete[] items;
    }

    class Iterator {
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = value_type&;

	pointer ptr;

    public:

        Iterator(pointer ptr) {
            this->ptr = ptr;
        }

        Iterator &operator++() {
            this->ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            this->ptr++;
            return tmp;
        }

        bool operator==(const Iterator &other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const Iterator &other) const {
            return this->ptr != other.ptr;
        }
    
        reference operator*() {
            return *ptr;
        }

        pointer operator->() {
            return ptr;
        }
    };

    class ConstIterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = value_type&;

        pointer ptr;

    public:
            
        ConstIterator(pointer ptr) {
            this->ptr = ptr;
        }

        ConstIterator &operator++() {
            this->ptr++;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            this->ptr++;
            return tmp;
        }

        bool operator==(const ConstIterator &other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const ConstIterator &other) const {
            return this->ptr != other.ptr;
        }

        const T operator*() {
            return *ptr;
        }

        const T* operator->() {
            return ptr;
        }
    };


    Iterator begin() {
        return Iterator(&this->GetFirstForIter());
    }

    Iterator end() {
        return Iterator(&this->GetLastForIter() + 1);
    }

    ConstIterator begin() const {
        return ConstIterator(&this->GetFirstForIter());
    }

    ConstIterator end() const {
        return ConstIterator(&this->GetLastForIter() + 1);
    }

private:
    T& GetFirstForIter() {
        return this->items[0];
    }

    T& GetLastForIter() {
        return this->items[this->size - 1];
    }

};
