#include <tuple>

template <class T> struct tuple_construct_t;

template <class... Ts> struct tuple_construct_t<std::tuple<Ts...>> {
  template <class... Args>
  static std::tuple<Ts...> make_tuple(Args&&... args) {
    return std::make_tuple(Ts{std::forward<Args>(args)...}...);
  }
};

template <class Tup, class... Args>
Tup construct_tuple(Args&&... args) {
    return tuple_construct_t<Tup>::make_tuple(std::forward<Args>(args)...);
}

struct Foo {int f; Foo(int i):f(i){} };
struct Bar {int b; Bar(int i):b(i){} };

struct NoDefault1 {
    NoDefault1(Foo foo, Bar bar) : i1(foo.f + bar.b) {};
    int i1;
};

struct NoDefault2 {
    NoDefault2(Foo foo, Bar bar) : i2(foo.f * bar.b) {};
    int i2;
};

#include <iostream>

int main() { 
  typedef std::tuple<NoDefault1, NoDefault2> myTuple;
  auto t = construct_tuple<myTuple>(Foo{5}, Bar{10});
  
  std::cout << std::get<0>(t).i1 << ' ' << std::get<1>(t).i2 << '\n';
}