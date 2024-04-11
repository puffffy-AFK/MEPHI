#pragma once

#include <iostream>

#include "DynamicArray.hpp"
#include "Sequence.hpp"

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> *buffer;

public:
    ArraySequence() : buffer(new DynamicArray<T>()) {}

    ArraySequence(T *items, int count) : buffer(new DynamicArray<T>(items, count)) {}

    ArraySequence(const DynamicArray<T> &input_array) : buffer(new DynamicArray<T>(input_array)) {}

    ArraySequence(const ArraySequence<T> &input_array) : buffer(new DynamicArray<T>(*input_array.buffer)) {}

    ArraySequence(Sequence<T> *input_sequence) : buffer(new DynamicArray<T>()) {
        for (int i = 0; i < input_sequence->GetLength(); i++) {
            this->buffer->Append(input_sequence->Get(i));
        }
    }

    ArraySequence<T> *Copy() const override {
        return new ArraySequence<T>(*this);
    }


    void Set(int index, T item) {
        this->buffer->Set(index, item);
    }

    T Get(int index) const override {
        return this->buffer->Get(index);
    }

    int GetLength() const override {
        return this->buffer->GetLength();
    }

    void Append(T item) override {
        this->buffer->Append(item);
    }

    void Prepend(T item) override {
        this->buffer->Prepend(item);
    }

    void InsertAt(T item, int index) override {
        this->buffer->InsertAt(item, index);
    }

    T& operator[](int index) override {
        return (*this->buffer)[index];
    }

    T operator[](int index) const override {
        return (*this->buffer)[index];
    }

    void swap(int i, int j) override {
        this->buffer->swap(i, j);
    }

    void Clear() override {
        this->buffer->Clear();
    }

    ~ArraySequence() {
        delete buffer;
    }

};

