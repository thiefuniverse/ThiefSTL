#include <iostream>
#include <memory>

#ifdef TEST_THIEF_STL
#include "log.hpp"
#include "shared_ptr.hpp"
#else
namespace thief_stl = std;
#endif

class TestSmartPtr {
private:
    int _id;

public:
    TestSmartPtr(int id) : _id(id) {
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
};
int main() {

#ifdef TEST_THIEF_STL
    thief_stl::set_log_level(LOG_LINE_LEVEL_ERROR);
#endif
    thief_stl::shared_ptr< TestSmartPtr > s1(new TestSmartPtr(999));
    std::cout << "s1 count: " << s1.use_count() << std::endl;
    thief_stl::shared_ptr< TestSmartPtr > s2 = s1;
    std::cout << "s1 count: " << s1.use_count() << std::endl;
    std::cout << "s2 count: " << s2.use_count() << std::endl;
    thief_stl::shared_ptr< TestSmartPtr > s3;
    s3 = s2;
    std::cout << "s3 count: " << s3.use_count() << std::endl;
    { s2 = thief_stl::shared_ptr< TestSmartPtr >(new TestSmartPtr(1000)); }
    std::cout << "s2 count: " << s2.use_count() << std::endl;
    thief_stl::shared_ptr< TestSmartPtr > s4;
    s2 = s4;
    if (s2) {
        std::cout << "test s2 bool true value" << std::endl;
    }
    std::cout << "s1 count: " << s1.use_count() << std::endl;
    std::cout << "s2 count: " << s2.use_count() << std::endl;
    std::cout << "s3 count: " << s3.use_count() << std::endl;
    return 0;
}
