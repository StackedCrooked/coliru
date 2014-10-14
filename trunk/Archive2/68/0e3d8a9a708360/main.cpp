#include <iostream>

struct t {
    void f() const { std::cout << "t()\n"; }
};

struct g : t {
    void f() const { std::cout << "g()\n"; }
};

void test(const t& t) {
    t.f();
}

// use a type trait
#include <type_traits>

struct has_my_function_impl {
    template<typename T>
    static auto test(int) -> decltype(std::declval<T>().f(), std::true_type{});
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_my_function : decltype(has_my_function_impl::test<T>(0)) {};

template<typename T>
void other(const T& t) {
    // assert?
    static_assert(has_my_function<T>::value, "needs f() member function");
    // could even go for duck typing I guess
    t.f();
}
int main() {
    g x;
    test(x);  // inheritance w/o virtual
    other(x); // traits
}