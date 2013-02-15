template<unsigned...> struct seq{ using type = seq; };
template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<unsigned N, class Seq = typename gen_seq<N>::type>
struct pair_array;
template<unsigned N, unsigned... Is>
struct pair_array<N, seq<Is...>>{
  using array_type = int[N][2];
  static array_type& get(){
    static array_type _array = {{Is, Is}...};
    return _array;
  }
};

#include <iostream>

int main(){
  auto& array = pair_array<5>::get();
  for(auto& e : array)
    std::cout << e[0] << " " << e[1] << " ";
}