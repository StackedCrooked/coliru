#include <iostream>

template<typename T>
struct has_foo
{
    template<typename U>
    constexpr static auto sfinae(U *obj) -> decltype(obj->foo(), bool()) { return true; }
    
    constexpr static auto sfinae(...) -> bool { return false; }
    
    constexpr static bool value = sfinae(static_cast<T*>(0));
};


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
