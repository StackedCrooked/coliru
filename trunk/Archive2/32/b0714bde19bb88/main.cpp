#include <type_traits>
#include <iostream>

template<typename Trait>
struct test
{
    template<int Value = Trait::f()>
    static std::true_type do_call(int){ return std::true_type(); }

    static std::false_type do_call(...){ return std::false_type(); }

    static bool call(){ return do_call(0); }
};

struct trait
{
    static int f(){ return 15; }
};

struct ctrait
{
    static constexpr int f(){ return 20; }
};

template<typename T>
constexpr int foo(const T&) {
    return 0;
}

template<typename T>
struct test2
{
    template<int Value = foo(T{})>
    static std::true_type do_call(int){ return std::true_type(); }

    static std::false_type do_call(...){ return std::false_type(); }

    static bool call(){ return do_call(0); }
};

struct C {
    constexpr C() {
    }
};

struct D {
    D() {
    }
};

int main()
{
    std::cout << "regular: " << test2<D>::call() << std::endl;
    std::cout << "constexpr: " << test2<C>::call() << std::endl;
}