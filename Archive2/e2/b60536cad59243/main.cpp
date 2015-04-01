#include <functional>
#include <utility>
#include <iostream>

template<class T, class A, class B>
struct sub{using type=T;};
template<class T, class B>
struct sub<T,T,B>{using type=B;};

template<class T, class A, class B>
using sub_t=typename sub<T,A,B>::type;

template<class Sig>
struct func;

struct recurse{};

template<class R, class...Args>
struct func<R(Args...)>{
  using Sig2=sub_t<R,recurse,func>(sub_t<Args,recurse,func>...);
  std::function<Sig2> impl;
  template<class...Ts>
  auto operator()(Ts&&...ts)const
  ->sub_t<R,recurse,func>
  {
    return impl(std::forward<Ts>(ts)...);
  }
};

int main() {
    using my_func1 = func< int() >;
    my_func1 f { {[]{return 7;}} };
    std::cout << f() << '\n';
    
    using my_func2 = func< recurse(int&) >;
    my_func2 f2;
    f2 = {{ [&](int& x){ ++x; return f2; } }};
    int x = 0;
    f2(x)(x)(x);
    std::cout << x << '\n';
}