#include <vector>

template<unsigned... Is> struct seq{};
template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class T> using Alias = T; // for temporary arrays

template<class F, class It, unsigned N, unsigned... Is>
auto invoke_2(F f, It (&&args)[N], seq<Is...>)
  -> decltype(f(*args[Is]...))
{
  return f(*args[Is]...);
}

template<class F, class Args, unsigned... Is>
auto invoke_1(F f, Args& cont, seq<Is...> s)
  -> decltype(invoke_2(f, std::declval<decltype(cont.begin())[sizeof...(Is)]>(), s))
{
  auto it = cont.begin();
  return invoke_2(f, Alias<decltype(it)[]>{(void(Is), ++it)...}, s);
}

template<unsigned ArgC, class F, class Args>
auto invoke(F f, Args& cont)
  -> decltype(invoke_1(f, cont, gen_seq<ArgC>{}))
{
  return invoke_1(f, cont, gen_seq<ArgC>{});
}

#include <type_traits>

template<unsigned I> using Uint = std::integral_constant<unsigned, I>;

struct invoke_test{
  template<class F, class T, class... Args, unsigned I>
  static auto eval(int, Uint<I> c) -> decltype(void(std::declval<F>()(std::declval<Args>()...)), c);
  template<class F, class T, class... Args, unsigned I>
  static auto eval(long, Uint<I>) -> decltype(eval<F, T, Args..., T>(0, Uint<I+1>{}));
};

template<class F, class T>
struct min_arity : decltype(invoke_test::eval<F, T>(0, Uint<0>{})){};

#include <iostream>

void f(int, int, int, int){ std::cout << "f(int,int,int,int) called\n"; }

struct X{
  void operator()(int, int, int){}
};

int main(){
    std::vector<int> args{1,2,3,4};
    invoke<4>(f, args);
    static_assert(min_arity<X, int>::value == 3, "eh");
}