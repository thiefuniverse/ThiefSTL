// -*- C++ -*-
#ifndef __ALGORITHM_H_
#define __ALGORITHM_H_

namespace thief_stl {

template < typename T >
void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

}  // namespace thief_stl

#endif  // __ALGORITHM_H_
