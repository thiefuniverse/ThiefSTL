#ifndef __WEAK_PTR_H_
#define __WEAK_PTR_H_
#include "algorithm.hpp"
#include "log.hpp"
#include "nullptr.hpp"
#include "shared_ptr.hpp"
#include "utility.hpp"

namespace thief_stl {
template < typename T >
class shared_ptr;

class __shared_weak_count;

template < typename T >
class weak_ptr {
public:
    // member type
    using element_type = T;

    // constructor
    weak_ptr() : __ptr(0), __cntptr(0) {}
    weak_ptr(const weak_ptr &another) : __ptr(another.__ptr), __cntptr(another.__cntptr) {
        if (__cntptr) {
            __cntptr->increase_weak();
        }
    }
    template < typename A >
    weak_ptr(const shared_ptr< A > &another) : __ptr(another.__ptr), __cntptr(another.__cntptr) {
        if (__cntptr) {
            __cntptr->increase_weak();
        }
    }
    weak_ptr(weak_ptr &&another) : __ptr(another.__ptr), __cntptr(another.__cntptr) {
        another.__cntptr = 0;
        another.__ptr = 0;
    }
    // destructor
    ~weak_ptr() {
        if (__cntptr) {
            __cntptr->decrease_weak();
            if (__cntptr->weak_use_count() == 0 && __cntptr->shared_use_count() == 0) {
                delete __cntptr;
                __cntptr = 0;
            }
        }
    }
    // assignment
    weak_ptr &operator=(const weak_ptr &another) {
        weak_ptr(another).swap(*this);
        return *this;
    }
    weak_ptr &operator=(weak_ptr &&another) {
        weak_ptr(thief_stl::move(another)).swap(*this);
        return *this;
    }
    template < typename A >
    weak_ptr &operator=(const shared_ptr< A > &another) {
        weak_ptr(another).swap(*this);
        return *this;
    }

    // modifiers
    void reset() {
        weak_ptr().swap(*this);
    }

    void swap(weak_ptr &another) {
        thief_stl::swap(__cntptr, another.__cntptr);
        thief_stl::swap(__ptr, another.__ptr);
    }

    // observers
    long use_count() {
        if (__cntptr) {
            return __cntptr->shared_use_count();
        }
        return 0;
    }
    bool expired() {
        return use_count() == 0;
    }

    shared_ptr< T > lock() {
        shared_ptr< T > ret;
        ret.__cntptr = __cntptr;
        ret.__ptr = __ptr;
        if (__cntptr) {
            __cntptr->increase_shared();
        }
        return ret;
    }

private:
    T *__ptr;
    __shared_weak_count *__cntptr;
};

}  // namespace thief_stl
#endif  // __WEAK_PTR_H_
