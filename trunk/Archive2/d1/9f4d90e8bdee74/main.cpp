#include <type_traits>



template <class T> struct Foo {
    static_assert(std::is_same<T, float>::value, "I take only floats, you fool");
}; 

int main() {Foo<int> f;}
