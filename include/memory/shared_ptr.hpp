#ifndef __SHARED_PTR_H_
#define __SHARED_PTR_H_

namespace thief_stl {

template < typename T >
class shared_ptr {

public:
    using element_type = T;

    shared_ptr< T >(T *ptr) {}
    shared_ptr< T > &operator=(shared_ptr< T > &another_ptr) {}

    // some practical overload functions
    void reset(T *ptr) {}

    void swap(T *ptr) {}

    T *get() {}
};

};      // namespace thief_stl
#endif  // __SHARED_PTR_H_
