#ifndef __SHARED_PTR_H_
#define __SHARED_PTR_H_

#include "algorithm.hpp"
#include "log.hpp"
#include "nullptr.hpp"
#include "utility.hpp"

namespace thief_stl {
template < typename T >
class weak_ptr;

class __shared_weak_count {
public:
    __shared_weak_count(long shared_refs = 0, long weak_refs = 0) : shared_count(shared_refs), weak_count(weak_refs) {}
    long shared_use_count() {
        return shared_count;
    }
    long weak_use_count() {
        return weak_count;
    }
    void increase_shared() {
        ++shared_count;
    }
    void increase_weak() {
        ++weak_count;
    }
    void decrease_shared() {
        --shared_count;
    }
    void decrease_weak() {
        --weak_count;
    }
    ~__shared_weak_count() {
        LOG_INFO_CONTENT("shared weak count destruct");
    }

private:
    long shared_count;
    long weak_count;
};

template < typename T >
class shared_ptr {

private:
    T *__ptr;
    __shared_weak_count *__cntptr;

public:
    using element_type = T;
    using type = shared_ptr< T >;

    // constructor
    shared_ptr() : __ptr(0), __cntptr(0) {}
    // shared_ptr(thief_stl::nullptr_t) : __ptr(0), __cntptr(0) {}
    shared_ptr(std::nullptr_t) : __ptr(0), __cntptr(0) {}
    shared_ptr(T *ptr) : __ptr(ptr) {
        LOG_INFO_LINE();
        __cntptr = new __shared_weak_count(1, 0);
    }
    shared_ptr(const shared_ptr< T > &another_shared) : __ptr(another_shared.__ptr), __cntptr(another_shared.__cntptr) {
        LOG_INFO_LINE();
        if (__cntptr) {
            __cntptr->increase_shared();
            LOG_INFO_CONTENT("increase shared count:  %ld\n", __cntptr->shared_use_count());
        }
    }
    shared_ptr(shared_ptr< T > &&another_shared) : __ptr(another_shared.__ptr), __cntptr(another_shared.__cntptr) {
        LOG_INFO_LINE();
        another_shared.__ptr = 0;
        another_shared.__cntptr = 0;
    }
    // assignment
    shared_ptr &operator=(const shared_ptr< T > &another_ptr) {
        LOG_INFO_LINE();
        shared_ptr< T >(another_ptr).swap(*this);
        return *this;
    }

    shared_ptr &operator=(shared_ptr< T > &&another_shared) {
        LOG_INFO_LINE();
        shared_ptr< T >(thief_stl::move(another_shared)).swap(*this);
        return *this;
    }

    ~shared_ptr() {
        LOG_INFO_LINE();
        if (__cntptr && __cntptr->shared_use_count() > 0) {
            __cntptr->decrease_shared();
            if (__cntptr->shared_use_count() == 0) {
                if (__ptr) {
                    delete __ptr;
                    __ptr = 0;
                }
                LOG_INFO_CONTENT("shared ptr destruct: weak count %ld", __cntptr->weak_use_count());
                if (__cntptr->weak_use_count() == 0) {
                    delete __cntptr;
                    __cntptr = 0;
                }
            }
        }
    }
    // modifiers
    void reset() {
        LOG_INFO_LINE();
        shared_ptr().swap(*this);
    }
    void reset(T *ptr) {
        LOG_INFO_LINE();
        shared_ptr(ptr).swap(*this);
    }

    void swap(shared_ptr< T > &another_shared) {
        LOG_INFO_LINE();
        // swap __ptr
        thief_stl::swap(__ptr, another_shared.__ptr);

        // swap __cntptr
        thief_stl::swap(__cntptr, another_shared.__cntptr);
    }

    // observers
    T *get() {
        return __ptr;
    }
    T &operator*() {
        return *__ptr;
    }
    T *operator->() {
        return __ptr;
    }
    operator bool() {
        return __ptr != 0;
    }

    // 返回当前的引用计数
    long use_count() {
        return __cntptr ? __cntptr->shared_use_count() : 0;
    }

    template < typename F >
    friend class weak_ptr;
};

//  make_shared
template < typename _Tp, typename... _Args >
shared_ptr< _Tp > make_shared(_Args &&... _args) {
    return shared_ptr< _Tp >(new _Tp(thief_stl::forward< _Args >(_args)...));
}

template < typename _Tp >
shared_ptr< _Tp > make_shared() {
    return shared_ptr< _Tp >(new _Tp());
}

template < typename _Tp, typename _A0 >
shared_ptr< _Tp > make_shared(_A0 _a0) {
    return shared_ptr< _Tp >(new _Tp(_a0));
}

};      // namespace thief_stl
#endif  // __SHARED_PTR_H_
