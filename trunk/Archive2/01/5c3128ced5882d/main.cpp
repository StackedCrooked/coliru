#include <iostream>
#include <type_traits>

template <typename... Arg>
struct has_mem_func_foo_impl {
    template <typename U, U>
    struct chk { };

    template <typename Class>
    static std::true_type has_foo(chk<void(Class::*)(Arg...), &Class::foo>*);

    template <typename>
    static std::false_type has_foo(...);
};

template <typename Class, typename... Arg>
struct has_mem_func_foo : decltype(has_mem_func_foo_impl<Arg...>::template has_foo<Class>(nullptr)) {};

struct bar {
    void foo(int) { }
};

struct qux {};

int main()
{
    static_assert( has_mem_func_foo<bar, int>::value, "bar has foo(int)" );
    static_assert( !has_mem_func_foo<qux, int>::value, "qux has no foo(int)" );
}
