template<unsigned... Is> struct seq{};
template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

enum Type {
    Alphabet,
    Number,
    Symbol,
    Other,
};

struct Table {
    Type _[128];
};

constexpr Type whichCategory(char c){ return (c > 63)? Alphabet : Other; /*lazy*/ }

template<unsigned... Is>
constexpr Table MagicFunction(seq<Is...>){
  return {{ whichCategory(Is)... }};
}

constexpr Table MagicFunction(){
  return MagicFunction(gen_seq<128>{});
}

#include <iostream>

int main(){
  constexpr Table table = MagicFunction();
  for(auto e : table._){
    std::cout << e;
  }
}