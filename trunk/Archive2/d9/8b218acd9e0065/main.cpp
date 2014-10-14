#include <iostream>
#include <type_traits>

struct has_mem_func_foo_impl {
    template <typename U, U>
    struct chk { };

    template <typename Class, typename... Arg>
    static std::true_type has_foo( int, chk<void(Class::*)(Arg...), &Class::foo>* = nullptr );

    template <typename, typename...>
    static std::false_type has_foo(...);
};

template <typename Class, typename... Arg>
struct has_mem_func_foo : decltype(has_mem_func_foo_impl::template has_foo<Class,Arg...>(0)) { };


struct bar {
    void foo(int) { }
};

int main() {
    static_assert( has_mem_func_foo<bar, int>::value, "bar has foo(int)" );
}