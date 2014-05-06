#include <iostream>

template<typename T>
struct allowed { template<typename U> operator U() = delete; operator T(); };

template<typename T>
struct has_foo
{
    template<typename U>
    constexpr static auto sfinae(U *obj) -> decltype(obj->foo(allowed<int>()), bool()) { return true; }
    
    constexpr static auto sfinae(...) -> bool { return false; }
    
    constexpr static bool value = sfinae(static_cast<T*>(0));
};


struct A {
    void foo(int) {}
};

struct B : public A {
    using A::foo;
};

struct C { void foo(unsigned int) {} };
struct D { void foo(short) {} };

int main() 
{
    std::cout << has_foo<A>::value << std::endl;
    std::cout << has_foo<B>::value << std::endl;
    std::cout << has_foo<C>::value << std::endl;
    std::cout << has_foo<D>::value << std::endl;
    std::cout << has_foo<int>::value << std::endl;
    return 0;
}
