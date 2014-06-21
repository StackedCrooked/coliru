#include <type_traits>
#include <cstdio>

template <typename T, typename W>
struct A {
    void foo(W) { }
    template<typename X=T,
      typename std::enable_if<!std::is_same<X, W>::value>::type* = 0>
    void foo(T, X* = 0) { }
    template<typename X = int,
      typename std::enable_if<!std::is_same<X, T>::value
      && !std::is_same<X, W>::value>::type* = 0>
    void foo(int, X* = 0) { }
};

struct S {};

int main() {
    A<S, int>().foo(S{});
}
