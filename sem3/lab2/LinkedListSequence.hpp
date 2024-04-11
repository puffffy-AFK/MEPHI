#pragma once

#include "LinkedList.hpp"
#include "Sequence.hpp"

template <class T> class LinkedListSequence : public Sequence<T> {

LinkedList<T> *buffer;

public:
    LinkedListSequence() : buffer(new LinkedList<T>()) {};

    LinkedListSequence(T *items, int count) : buffer(new LinkedList<T>(items, count)) {};

    LinkedListSequence(const LinkedList<T> &input_list) : buffer(new LinkedList<T>(input_list)) {};

    LinkedListSequence(const LinkedListSequence<T> &input_list) : buffer(new LinkedList<T>(*input_list.buffer)) {};

    LinkedListSequence(Sequence<T> *input_sequence) : buffer(new LinkedList<T>()) {
        for (int i = 0; i < input_sequence->GetLength(); i++) {
            this->buffer->Append(input_sequence->Get(i));
        }
    };

    LinkedListSequence<T> *Copy() const override {
        return new LinkedListSequence<T>(*this);
    }

    void Clear() override {
        this->buffer->Clear();
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
        return this->buffer->Get(index);
    }

    void swap(int i, int j) override {
        this->buffer->swap(i, j);
    }

    ~LinkedListSequence() {
        delete this->buffer;
    }

};


