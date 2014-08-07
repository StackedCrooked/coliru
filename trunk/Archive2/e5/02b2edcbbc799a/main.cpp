#include <cstdlib>
#include <memory>

struct MyStruct
{
    static void myFunc( void );

    //constructors
    MyStruct( void ) = delete;
};

struct free_deleter {
    void operator() (void* ptr) const {
        std::free(ptr);
    }
};

int main() {
    auto p = std::unique_ptr<MyStruct, free_deleter>{static_cast<MyStruct*>(std::malloc(sizeof(MyStruct)))};
    MyStruct a = *p;
    MyStruct b = std::move(a);
}
