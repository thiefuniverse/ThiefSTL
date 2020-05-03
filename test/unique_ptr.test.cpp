#include <iostream>

#ifdef TEST_THIEF_STL
#include "log.hpp"
#include "nullptr.hpp"
#include "unique_ptr.hpp"
#include "utility.hpp"
#else
#include <memory>
namespace thief_stl = std;
#endif

class TestSmartPtr {
private:
    int _id;

public:
    TestSmartPtr(int id) : _id(id) {
        std::cout << "construct TestSmartPtr " << id << std::endl;
    }
    TestSmartPtr(int id1, int id2, int id3) : _id(id3) {
        std::cout << "construct TestSmartPtr" << std::endl;
    }

    TestSmartPtr(const TestSmartPtr &another) {
        std::cout << "copy construct TestSmartPtr" << std::endl;
    }
    TestSmartPtr(TestSmartPtr &&another) {
        std::cout << "move construct TestSmartPtr" << std::endl;
    }
    ~TestSmartPtr() {
        std::cout << "destruct TestSmartPtr id " << _id << std::endl;
    }
    void print() {
        std::cout << "current id: " << _id << std::endl;
    }
};

void RunOnce(thief_stl::unique_ptr< TestSmartPtr > ptr) {
    ptr->print();
    std::cout << "run once done" << std::endl;
}
int main() {
    // set log level
#ifdef TEST_THIEF_STL
    thief_stl::set_log_level(LOG_LINE_LEVEL_ERROR);
#endif

    // constructor, assignment
    thief_stl::unique_ptr< TestSmartPtr > s1(new TestSmartPtr(999));
    // thief_stl::unique_ptr< TestSmartPtr > s2 = s1;  // can't compile, call to deleted constructor
    {
        thief_stl::unique_ptr< TestSmartPtr > s2 = thief_stl::move(s1);
        RunOnce(thief_stl::move(s2));
        std::cout << "after run once" << std::endl;
    }

    // release
    thief_stl::unique_ptr< TestSmartPtr > s3(new TestSmartPtr(1000));
    TestSmartPtr *s3_ptr = s3.release();
    std::cout << "after s3 release" << std::endl;
    delete s3_ptr;

    // get, reset, operator bool
    thief_stl::unique_ptr< TestSmartPtr > s4(new TestSmartPtr(2000));
    s4.get()->print();
    (*s4).print();

    if (s4) {
        std::cout << "s4 now own some object" << std::endl;
    }
    s4.reset();
    if (!s4) {
        std::cout << "s4 now doesn't own some object" << std::endl;
    }

    thief_stl::unique_ptr< TestSmartPtr > s5(new TestSmartPtr(3000));
    {
        thief_stl::unique_ptr< TestSmartPtr > s6(new TestSmartPtr(4000));
        s6.swap(s5);
        std::cout << "swap done" << std::endl;
    }

    return 0;
}
