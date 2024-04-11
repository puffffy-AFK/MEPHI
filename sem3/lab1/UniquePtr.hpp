#ifndef UNIQPTR_HPP
#define UNIQPTR_HPP

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    UniquePtr(T* p = nullptr) : ptr(p) {}

    ~UniquePtr() {
        delete ptr;
    }

    UniquePtr(const UniquePtr& up) = delete;

    UniquePtr& operator=(const UniquePtr& up) = delete;

    UniquePtr(UniquePtr&& up) : ptr(up.ptr) {
        up.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& up) {
        if (this != &up) {
            delete ptr;
            ptr = up.ptr;
            up.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    operator bool() const {
        return ptr != nullptr;
    }

    T* release() {
        T* oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }

    T* get() const {
        return ptr;
    }

    void reset(T* p = nullptr) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }
};

#endif