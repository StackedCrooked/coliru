#include <tuple>

struct zipper_tag{};

static zipper_tag const zipper{};

template<class C>
std::tuple<zipper_tag, C&> zip(C& c){ return std::tie(zipper, c); }

template<class... Ts, class C>
std::tuple<zipper_tag, Ts..., C&> operator&(std::tuple<zipper_tag, Ts...> const& t, C&& c){
  return std::tuple_cat(t, std::tie(c));
}

template<unsigned... Is> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class T> using Invoke = typename T::type;

template<unsigned I> using GenSeq = Invoke<gen_seq<I>>;

template<class S> struct tail;
template<unsigned I, unsigned... Is>
struct tail<seq<I, Is...>> : seq<Is...>{};

template<class S> using Tail = Invoke<tail<S>>;

template<class T, class F, unsigned... Is>
void expand(T const& t, F f, seq<Is...>){
  f(std::get<Is>(t)...);
}

template<class... Ts, class F>
void operator|(std::tuple<zipper_tag, Ts...> const& t, F f){
  return expand(t, f, Tail<GenSeq<sizeof...(Ts)+1>>{});
}

template<class C, class F>
auto operator|(C const& c, F f) -> decltype(f(c)){ return f(c); }

#include <vector>
#include <iostream>

struct swallow{ template<class... Ts> swallow(Ts&&...){} };

struct foo{
  template<class T, class... Ts>
  void operator()(T&& v, Ts&&... vs){
    std::cout << v[0];
    swallow{ (std::cout << ", " << vs[0])... };
  }
};

std::vector<int> drop1(std::vector<int> const& v){
  return std::vector<int>(++v.begin(), v.end());
}

int main(){
  std::vector<int> v{42, 84};
  zip(v) & v & (v | drop1) & v | foo();
}
