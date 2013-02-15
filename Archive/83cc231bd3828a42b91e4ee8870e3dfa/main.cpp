#include <tuple>

template<unsigned...> struct seq{};
template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class T>
struct match_value{ void operator=(T const&){} T value; };

template<class T>
match_value<T> match(T value){ return {value}; }

template<class... Args>
struct match_tuple{
    std::tuple<Args&...> _args;
    
    match_tuple(Args&... args)
      : _args(args...){}
      
    template<class... UArgs>
    std::tuple<Args&...> operator=(std::tuple<UArgs...> const& other){
        if(try_match(other, gen_seq<sizeof...(Args)>{}))
          _args = other;
        return _args;
    }
    
    template<class Tuple, unsigned... Is>
    bool try_match(Tuple const& other, seq<Is...>){
        return all_of(check_match(std::get<Is>(_args), std::get<Is>(other))...);
    }
    template<class T, class U>
    static bool check_match(T&, U const&){ return true; }
    template<class T, class U>
    static bool check_match(match_value<T>& v, U const& u){ return v.value == u; }
    
    static bool all_of(bool b){ return b; }
    template<class... Bs>
    static bool all_of(bool b, Bs... vs){ return b && all_of(vs...); }
};

template<class... Args>
match_tuple<Args&...> match_tie(Args&&... args){ return {args...}; }

#include <iostream>

int main(){
  int a = 1, b = 2, c = 3;
  match_tie(a, b, match(42), c) = std::make_tuple(10, 20, 42, 30);
  std::cout << a << ", " << b << ", " << c << "\n";
  match_tie(a, b, match(42), c) = std::make_tuple(100, 200, 1337, 300);
  std::cout << a << ", " << b << ", " << c << "\n";
 
}