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

struct placement_deleter {
    template <typename T>
    void operator() (T* ptr) const {
        ptr->~T();
    }
};

int main() {
    std::aligned_storage<sizeof(MyStruct), alignof(MyStruct)>::type buffer;
    auto p1 = std::unique_ptr<MyStruct, placement_deleter>{
        reinterpret_cast<MyStruct*>(&buffer)
    };
    MyStruct a = *p1;

    auto p2 = std::unique_ptr<MyStruct, free_deleter>{
        static_cast<MyStruct*>(std::malloc(sizeof(MyStruct)))
    };
    MyStruct b = std::move(*p2);
}
