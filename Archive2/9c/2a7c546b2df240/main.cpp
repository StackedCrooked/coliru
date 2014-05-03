#include <iostream>

struct A {
    void func() {
        std::cerr << "A::func()" << std::endl;
    }
};
struct B {
    int func() {
        std::cerr << "B::func()" << std::endl;
        return 1;
    }
};

// type_sink takes a type, and discards it.  type_sink_t is a C++1y style using alias for it
template<typename T> struct type_sink { typedef T type; };
template<typename T> using type_sink_t = typename type_sink<T>::type;

// has_func is a traits class that inherits from `true_type` iff the expression t.func()
// is a valid one.  `std::true_type` has `::value=true`, and is a good canonical way to
// represent a compile-time `bool`ean value.
template<typename T,typename=void> struct has_func : std::false_type {};
template<typename T> struct has_func<
  T,
  type_sink_t< decltype( std::declval<T&>().func() ) >
> : std::true_type {};

// helpers for tag dispatching.
namespace helper_ns {
  template<typename T> void anotherFunc( T&& t, std::false_type /* has_func */ ) {}
  template<typename T> void anotherFunc( T&& t, std::true_type /* has_func */ ) {
    std::forward<T>(t).func();
  }
}
// take the type T, determine if it has a .func() method.  Then tag dispatch
// to the correct implementation:
template<typename T> void anotherFunc(T t) {
  helper_ns::anotherFunc( std::forward<T>(t), has_func<T>() );
}

int main() {
    A a;
    B b;
    anotherFunc(a);
    anotherFunc(b);
}