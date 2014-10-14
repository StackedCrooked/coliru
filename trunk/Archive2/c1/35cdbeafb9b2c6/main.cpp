#include <iostream>
#include <type_traits>


template<typename, typename T>
struct has_mem_func_foo;

template<typename Class, typename Ret, typename... Args>
struct has_mem_func_foo<Class, Ret(Args...)> {
private:
    template<typename T>
    static auto check(T*)
    -> typename
        std::is_same<decltype( std::declval<T>().foo( std::declval<Args>()... ) ),
            Ret   
        >::type;  

    template<typename>
    static constexpr std::false_type check(...);

public:
    static constexpr bool value =  decltype(check<Class>(0))::value;
};

struct bar {
    void foo(int) { }
};

int main() {
    static_assert( has_mem_func_foo<bar, void(int)>::value,     "bar has foo(int)" );
    static_assert( has_mem_func_foo<bar, int(int)>::value,  "bar has foo(double)" );
}