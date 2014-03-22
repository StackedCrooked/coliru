#include <tuple>

template <class ... Ts, class ... Args>
std::tuple<Ts...> cartesian_make_tuple(Args && ... args)
{
    return std::make_tuple(Ts{ std::forward<Args>(args)... } ...);
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
  auto t = cartesian_make_tuple<NoDefault1, NoDefault2>(Foo{5},Bar{10});
  
  std::cout << std::get<0>(t).i1 << ' ' << std::get<1>(t).i2 << '\n';
}