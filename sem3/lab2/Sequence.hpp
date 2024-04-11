#pragma once

#include <tuple>

#include "Collection.hpp"

template <class T> class Sequence : public Collection<T> {

public:
    virtual T Get(int) const = 0;

    virtual void Append(T) = 0;
    virtual void Prepend(T) = 0;
    virtual void InsertAt(T, int) = 0;
    virtual Sequence<T>* Copy() const = 0;
    virtual void swap(int, int) = 0;
    virtual void Clear() = 0;


    virtual T& operator[](int) = 0;
    virtual T operator[](int) const = 0;

    virtual ~Sequence() {};
};
