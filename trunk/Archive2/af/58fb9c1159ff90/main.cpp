#include <iostream>
#include <type_traits>

struct bar {
    void foo(int) { }
};

template<class...Args>
struct test {
    template <typename U, U>
    struct chk { };

    template <typename Class>
    static constexpr std::true_type has_foo(chk<void(Class::*)(Args...), &Class::foo>*) {  return {}; }
    
    template <typename>
    static constexpr std::false_type has_foo(...) { return {}; }
};

template<class...Args>
struct has_mem_func_foo_impl {
    template <typename U, U>
    struct chk { };

    template <typename Class>
    static constexpr std::true_type has_foo(chk<void(Class::*)(Args...), &Class::foo>*) { return {}; }

    template <typename>
    static constexpr std::false_type has_foo(...) { return {}; }
};

template <typename Class, typename... Arg>
struct has_mem_func_foo : decltype(has_mem_func_foo_impl<Arg...>::template has_foo<Class>(nullptr)) { };



int main() {
    static_assert( has_mem_func_foo<bar, int>::value, "bar has foo(int)" );
}