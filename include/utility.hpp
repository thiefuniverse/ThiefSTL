#ifndef __UTILITY_H_
#define __UTILITY_H_

#include "type_traits.hpp"

namespace thief_stl {

template < typename T >
typename thief_stl::remove_reference< T >::type &&move(T &&t) {
    return static_cast< typename thief_stl::remove_reference< T >::type && >(t);
}

template < typename T >
T &&forward(typename thief_stl::remove_reference< T >::type &t) {
    return static_cast< T && >(t);
}

}  // namespace thief_stl

#endif  // __UTILITY_H_
