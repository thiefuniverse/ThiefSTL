#include <iostream>

#ifdef TEST_THIEF_STL
#include "log.hpp"
#include "nullptr.hpp"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"
#else
#include <cstddef>
#include <memory>
namespace thief_stl = std;
#endif

class TestSmartPtr {
private:
    int _id;

public:
    TestSmartPtr(int id) : _id(id) {
        std::cout << "construct TestSmartPtr" << std::endl;
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
int main() {

#ifdef TEST_THIEF_STL
    thief_stl::set_log_level(LOG_LINE_LEVEL_ERROR);
#endif
    thief_stl::weak_ptr< TestSmartPtr > s2;
    {
        thief_stl::shared_ptr< TestSmartPtr > s1(new TestSmartPtr(999));
        std::cout << "s1 count: " << s1.use_count() << std::endl;

        s2 = s1;
        std::cout << "s1 count: " << s1.use_count() << std::endl;

        auto s3 = s2.lock();
        s3->print();
        thief_stl::shared_ptr< TestSmartPtr > s4;
        s4 = s3;
    }
    if (s2.expired()) {
        std::cout << "s2 is expired" << std::endl;
    }

    return 0;
}
