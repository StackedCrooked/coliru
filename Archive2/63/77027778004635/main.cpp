#include <cstdlib>
#include <type_traits>
#include <utility>

struct MyStruct
{
    static void myFunc( void );

    //constructors
    MyStruct( void ) = delete;
};

int main() {
    std::aligned_storage<sizeof(MyStruct), alignof(MyStruct)>::type buffer;
    auto p1 = reinterpret_cast<MyStruct*>(&buffer);
    MyStruct a = *p1;

    auto p2 = static_cast<MyStruct*>(std::malloc(sizeof(MyStruct)));
    MyStruct b = std::move(*p2);
}
