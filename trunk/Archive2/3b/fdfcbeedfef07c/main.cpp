#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdlib>

struct fake_anything {
  template<class T>operator T&() const;
  template<class T>operator T&&() const;
  template<class T>operator T const&() const;
  template<class T>operator T const&&() const;
};
template<class>using void_t=void;

template<class Sig, class=void>
struct can_invoke:std::false_type{};
template<class F, class...Args>
struct can_invoke<F(Args...),
  void_t< decltype( std::declval<F>()( std::declval<Args...>() ) ) >
> : std::true_type
{};

template<unsigned...>struct indexes{using type=indexes;};
template<unsigned Max,unsigned...Is>struct make_indexes:make_indexes<Max-1,Max-1,Is...>{};
template<unsigned...Is>struct make_indexes<0,Is...>:indexes<Is...>{};
template<unsigned max>using make_indexes_t=typename make_indexes<max>::type;

template<class T,unsigned>using unpacker=T;

template<class F, class A, class indexes>
struct nary_help;
template<class F, class A, unsigned...Is>
struct nary_help<F,A,indexes<Is...>>:
  can_invoke<F( unpacker<A,Is>... )>
{};
template<class F, unsigned N>
struct has_n_arity:
  nary_help<F, fake_anything, make_indexes_t<N>>
{};

template<class F, unsigned Min=0, unsigned Max=100>
struct max_arity{
  enum{Mid=(Max+Min)/2};
  enum{a=max_arity<F,Min,Mid>::value, b=max_arity<F,Mid+1,Max>::value };
  enum{value=b>a?b:a};
};
template<class F, unsigned X>
struct max_arity<F,X,X>{
  enum{value=has_n_arity<F,X>::value?(int)X:-1};
};

template<class F, unsigned Min=0, unsigned Max=100>
struct min_arity{
  enum{Mid=(Max+Min)/2};
  enum{a=min_arity<F,Min,Mid>::value, b=min_arity<F,Mid+1,Max>::value };
  enum{value=a<b?a:b};
};
template<class F, unsigned X>
struct min_arity<F,X,X>{
  enum{value=has_n_arity<F,X>::value?(int)X:-1};
};

int main()
{
    auto lambda = [] (auto y)  { return x + y; };
    
    std::cout << min_arity<decltype(lambda)>::value << std::endl;
}
