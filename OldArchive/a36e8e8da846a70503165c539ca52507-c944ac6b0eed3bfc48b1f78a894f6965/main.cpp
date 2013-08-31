#include <vector>
#include <utility>
#include <type_traits>

template<typename T, typename U>
struct Y
{
    template <typename TT, typename UU>
    Y(TT&& t, UU&& u) : t(std::forward<TT>(t)), u(std::forward<UU>(u)) {}

    T t;
    U u;
};

template <typename T>
struct capture_type { typedef const T& type; };
template <typename T>
struct capture_type<T&&> { typedef T type; };

template <typename T, typename U>
Y<typename capture_type<T&&>::type, typename capture_type<U&&>::type>
CreateY(T&& t, U&& u) {
    return {std::forward<T>(t), std::forward<U>(u)};
}

#include <cassert>
#include <iostream>
#include <typeinfo>

struct A {
    int x;

    A(int x) : x(x) { std::cout << "A[" << this << "](" << x << ")\n"; }
    A(const A& other) : x(other.x) { std::cout << "A[" << this << "](&" << &other << ")\n"; }
    A(A&& other) : x(std::move(other.x)) { other.x = 0; std::cout << "A[" << this << "](&&" << &other << ")\n"; }
    ~A() { std::cout << "~A[" << this << "]()\n"; }
};

int main() {
    A foo = 42;
    int x = 13;
    auto a = CreateY(foo, std::move(x));
    assert(&a.t == &foo);
    assert(&a.u != &x);
    static_assert(!std::is_same<A const&,capture_type<A&>::type>::value, "BOOM!");
}
