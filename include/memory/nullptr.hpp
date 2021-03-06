#ifndef __NULLPTR_H_
#define __NULLPTR_H_

namespace thief_stl {

class nullptr_t {
public:
    nullptr_t() {}

    template < class T >
    operator T *() {
        return 0;
    }
    template < class T, class P >
    operator T P::*() {
        return 0;
    }
    friend bool operator==(nullptr_t, nullptr_t) {
        return true;
    }

    friend bool operator!=(nullptr_t, nullptr_t) {
        return false;
    }

private:
    void operator&() {}
};
inline nullptr_t __get_nullptr() {
    return nullptr_t();
}
}  // namespace thief_stl

#define nullptr thief_stl::__get_nullptr()

#endif  // __NULLPTR_H_
