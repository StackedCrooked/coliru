#include <iostream>

namespace details
{
    template<typename U>
    auto sfinae(U *obj) -> decltype(obj->foo(), std::true_type());
    
    auto sfinae(...) -> std::false_type;
}
template<typename T>
struct has_foo : decltype(details::sfinae(static_cast<T*>(0))) {};

struct A {
    void foo() {}
};

struct B : public A {
    using A::foo;
};

struct C{};

int main() 
{
    std::cout << has_foo<A>::value << std::endl;
    std::cout << has_foo<B>::value << std::endl;
    std::cout << has_foo<C>::value << std::endl;
    std::cout << has_foo<int>::value << std::endl;
    return 0;
}
