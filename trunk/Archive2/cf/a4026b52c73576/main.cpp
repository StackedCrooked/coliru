#include <iostream>
#include <utility>

#define DEFINE(Name)                        \
template<class... T>                        \
decltype(auto) Name(T&&... t)               \
{                                           \
    return base.Name(std::forward<T>(t)...);\
}

template <typename Base>
struct wrapper
{
  Base base;
  DEFINE(foo);
  DEFINE(bar);
};

struct foo_no_bar
{
  void foo(int)   const { std::cerr << __PRETTY_FUNCTION__ << '\n'; }
  int foo(double) const { std::cerr << __PRETTY_FUNCTION__ << '\n'; return 1; }
};

struct foo_and_bar
{
  void foo() const { std::cerr << __PRETTY_FUNCTION__ << '\n'; }
  void bar()       { std::cerr << __PRETTY_FUNCTION__ << '\n'; }
};

int main()
{
  wrapper<foo_and_bar> f;
  f.foo();
  f.bar();
  wrapper<foo_no_bar> b;
  b.foo(1);
  b.foo(1.0);
}
