#include <iostream>
#include <type_traits>

template <typename T>
struct is_foo {
    template<typename U>
    static auto check(int) ->
    decltype( static_cast< void (U::*)() const >(&U::foo), std::true_type() );
    //                     ^^^^^^^^^^^^^^^^^^^
    //                     the desired signature goes here

    template<typename>
    static std::false_type check(...);

    static constexpr bool value = decltype(check<T>(0))::value;
};

struct A {
void foo() const;
};

struct A1 : public A {};

struct B { void foo(); };
struct C { int foo() const; };

template <typename T>
struct D : public T {};

struct O {
    int foo() volatile;
    void foo() const;
};

int main() {
    std::cout << "Good examples (should print 1)\n";
    std::cout << is_foo<A>::value << '\n';
    std::cout << is_foo<A1>::value << '\n';
    std::cout << is_foo<D<A>>::value << '\n';
    std::cout << is_foo<D<A1>>::value << '\n';
    std::cout << is_foo<O>::value << '\n';

    std::cout << "Bad examples (should print 0)\n";
    std::cout << is_foo<B>::value << '\n';
    std::cout << is_foo<C>::value << '\n';
    std::cout << is_foo<D<B>>::value << '\n';
    std::cout << is_foo<D<C>>::value << '\n';

    return 0;
}