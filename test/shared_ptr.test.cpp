#include <iostream>
#include <memory>

#ifdef TEST_THIEF_STL
#include "log.hpp"
#include "nullptr.hpp"
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

    int nullptr_val = thief_stl::nullptr;
    std::cout << "nullptr val: " << nullptr_val << std::endl;
    thief_stl::nullptr_t null_a;

    if (thief_stl::nullptr == thief_stl::nullptr) {
        std::cout << "thief stl nullptr equal" << std::endl;
    }
    // test empty int* pointer
    int *int_ptr = null_a;
    std::cout << int_ptr << std::endl;
    if (int_ptr == thief_stl::nullptr) {
        std::cout << "thief stl nullptr with int ptr equal" << std::endl;
    }
    int i = 90;
    int_ptr = &i;
    if (int_ptr != thief_stl::nullptr) {
        std::cout << "thief stl nullptr not equal" << std::endl;
    }

    // test make_shared
    auto s5 = thief_stl::make_shared< TestSmartPtr >(2000);
    s2 = s5;

    auto s6 = thief_stl::make_shared< TestSmartPtr >(1000, 2000, 3000);

    // test operator overload function
    (*s6).print();
    s5->print();
    std::cout << s4.get() << std::endl;
    s2.get()->print();

    return 0;
}
