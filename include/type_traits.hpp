#ifndef __TYPE_TRAITS_H_
#define __TYPE_TRAITS_H_

namespace thief_stl {

template < typename T >
struct remove_reference {
    typedef T type;
};
template < typename T >
struct remove_reference< T & > {
    typedef T type;
};
template < typename T >
struct remove_reference< T && > {
    typedef T type;
};

}  // namespace thief_stl

#endif  // __TYPE_TRAITS_H_
