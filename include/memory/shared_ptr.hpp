#ifndef __SHARED_PTR_H_
#define __SHARED_PTR_H_

#include "algorithm.hpp"
#include "log.hpp"
#include "nullptr.hpp"
#include "utility.hpp"
//#include <cstddef>

namespace thief_stl {

template < typename T >
class shared_ptr {

private:
    class __shared_count {
    public:
        __shared_count(long __refs = 0) : count(__refs) {}
        long use_count() {
            return count;
        }
        void increase() {
            ++count;
        }
        void decrease() {
            --count;
        }

    private:
        long count;
    };

    T *__ptr;
    __shared_count *__cntptr;

public:
    using element_type = T;
    using type = shared_ptr< T >;

    // constructor
    shared_ptr() : __ptr(0), __cntptr(0) {}
    // shared_ptr(thief_stl::nullptr_t) : __ptr(0), __cntptr(0) {}
    shared_ptr(std::nullptr_t) : __ptr(0), __cntptr(0) {}
    shared_ptr(T *ptr) : __ptr(ptr) {
        LOG_INFO_LINE();
        __cntptr = new __shared_count(1);
    }
    shared_ptr(const shared_ptr< T > &another_shared) : __ptr(another_shared.__ptr), __cntptr(another_shared.__cntptr) {
        LOG_INFO_LINE();
        if (__cntptr) {
            __cntptr->increase();
            LOG_INFO_CONTENT("increase count:  %ld\n", __cntptr->use_count());
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
        if (__cntptr && __cntptr->use_count() >= 0) {
            __cntptr->decrease();
            if (__cntptr->use_count() == 0) {
                if (__ptr) {
                    delete __ptr;
                    __ptr = 0;
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
        return __cntptr ? __cntptr->use_count() : 0;
    }
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
