#ifndef __UNIQUE_PTR_H_
#define __UNIQUE_PTR_H_

#include "algorithm.hpp"
#include "log.hpp"
#include "nullptr.hpp"

namespace thief_stl {

// define default deleter
template < typename T >
struct default_delete {
    default_delete() = default;
    void operator()(T *__ptr) {
        delete __ptr;
    }
};

template < typename T >
struct default_delete< T[] > {
    default_delete() = default;
    void operator()(T *__ptr) {
        delete[] __ptr;
    }
};

template < typename T, typename D = default_delete< T > >
class unique_ptr {
public:
    using pointer = T *;
    using element_type = T;
    using delete_type = D;

    unique_ptr() : __ptr(nullptr) {}
    unique_ptr(nullptr_t) : __ptr(nullptr) {}
    unique_ptr(T *ptr) : __ptr(ptr) {}
    unique_ptr(T *ptr, D deleter) : __ptr(ptr), __deleter(deleter) {}
    unique_ptr(unique_ptr &&another) : __ptr(another.release()), __deleter(another.get_deleter()) {
        LOG_INFO_CONTENT("rvalue constructor");
    }

    ~unique_ptr() {
        LOG_INFO_CONTENT("unique ptr destruct");
        reset();
    }
    unique_ptr &operator=(unique_ptr &&another) {
        reset(another.release());
        __deleter = another.get_deleter();
        return *this;
    }

    T *release() {
        T *ret_ptr = __ptr;
        __ptr = nullptr;
        return ret_ptr;
    }
    void reset(T *new_ptr = nullptr) {
        T *old_ptr = __ptr;
        __ptr = new_ptr;
        if (old_ptr) {
            __deleter(old_ptr);
        }
    }
    void swap(unique_ptr &another) {
        thief_stl::swap(__ptr, another.__ptr);
    }

    T *get() {
        return __ptr;
    }
    D get_deleter() {
        return __deleter;
    }

    explicit operator bool() {
        return get() != nullptr;
    }
    T &operator*() {
        return *__ptr;
    }
    T *operator->() {
        return __ptr;
    }
    // forbid copy constructor and copy assignment
    unique_ptr(unique_ptr const &) = delete;
    unique_ptr &operator=(unique_ptr const &) = delete;

private:
    T *__ptr;
    D __deleter;
};

}  // namespace thief_stl
#endif  // __UNIQUE_PTR_H_
