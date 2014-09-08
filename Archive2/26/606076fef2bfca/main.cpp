#include <iostream>

struct fake_anything {
  fake_anything(fake_anything const&);
  fake_anything();
  fake_anything&operator=(fake_anything const&);
  template<class T>operator T&() const;
  template<class T>operator T&&() const;
  template<class T>operator T const&() const;
  template<class T>operator T const&&() const;
  fake_anything operator*() const;
  fake_anything operator++() const;
  fake_anything operator++(int) const;
  fake_anything operator->() const;
  template<class T>fake_anything(T&&);
};
fake_anything operator+(fake_anything, fake_anything);
fake_anything operator-(fake_anything, fake_anything);
fake_anything operator*(fake_anything, fake_anything);
fake_anything operator/(fake_anything, fake_anything);
// etc

template<class>using void_t=void;

template<class Sig, class=void>
struct can_invoke:std::false_type{};
template<class F, class...Args>
struct can_invoke<F(Args...),
  void_t< decltype( std::declval<F>()( std::declval<Args>()... ) ) >
> : std::true_type
{};

template<class Sig>struct is_sig:std::false_type{};
template<class R, class...Args>struct is_sig<R(Args...)>:std::true_type{};

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

template<class F, unsigned Min=0, unsigned Max=10>
struct max_arity{
  enum{Mid=(Max+Min)/2};
  enum{
        lhs = max_arity<F,Min,Mid>::value,
        rhs = max_arity<F,Mid+1,Max>::value,
        value = lhs>rhs?lhs:rhs,
  };
};
template<class F, unsigned X>
struct max_arity<F,X,X>:
    std::integral_constant<int, has_n_arity<F,X>::value?(int)X:-1>
{};

template<class F, unsigned Min=0, unsigned Max=10>
struct min_arity{
  enum{Mid=(Max+Min)/2};
  enum{
        lhs = min_arity<F,Min,Mid>::value,
        rhs = min_arity<F,Mid+1,Max>::value,
        value = lhs<rhs?lhs:rhs,
  };
};
template<class F, unsigned X>
struct min_arity<F,X,X>:
	std::integral_constant<unsigned,has_n_arity<F,X>::value?X:(unsigned)-1>
{};

auto test1 = [](auto x, auto y)->bool { return x < y; };
auto test2 = [](auto x, auto y) { return x + y; };
auto test3 = [](auto x) { return x.y; };

int main() {
    std::cout << can_invoke< decltype(test1)( fake_anything, fake_anything ) >::value << "\n";
    std::cout << can_invoke< decltype(test1)( int, int ) >::value << "\n";
//    decltype( std::declval<decltype(test1)>()( std::declval<Args...>() ) ) x;
    std::cout << has_n_arity< decltype(test1), 2 >::value << "\n";
	std::cout << max_arity< decltype(test1) >::value << "\n";
	std::cout << max_arity< decltype(test2) >::value << "\n";
    std::cout << max_arity< decltype(test3) >::value << "\n";
	// your code goes here
	return 0;
}