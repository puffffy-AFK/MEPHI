#include <cstddef>
#include <functional>

#ifndef SHRD_PTR_HPP
#define SHRD_PTR_HPP

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* refCount;
    std::function<void(T*)> deleter;

    void release() {
        if (--(*refCount) == 0) {
            deleter(ptr);
            delete refCount;
        }
    }

public:
    SharedPtr(T* p = nullptr, std::function<void(T*)> d = [](T* p) { delete p; }) 
        : ptr(p), refCount(new size_t(1)), deleter(d) {}

    ~SharedPtr() {
        release();
    }

    SharedPtr(const SharedPtr& sp) : ptr(sp.ptr), refCount(sp.refCount), deleter(sp.deleter) {
        (*refCount)++;
    }

    T& operator[](std::size_t idx) {
        return ptr[idx];
    }

    SharedPtr& operator=(const SharedPtr& sp) {
        if (this != &sp) {
            release();
            ptr = sp.ptr;
            refCount = sp.refCount;
            deleter = sp.deleter;
            (*refCount)++;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }

    size_t use_count() const {
        return *refCount;
    }

    operator bool() const {
        return ptr != nullptr;
    }
};

#endif // SHRD_PTR_HPP