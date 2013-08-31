#include <array>
#include <iostream>

template<unsigned...> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is> struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is> struct gen_seq<0, Is...> : seq<Is...>{};

template<unsigned I>
using GenSeq = typename gen_seq<I>::type;

template<class T, unsigned N, unsigned... Is>
std::array<T, N> as_array(T (&a)[N], seq<Is...>){ return {{ a[Is]... }}; }

template<class T, unsigned N>
std::array<T, N> as_array(T (&a)[N]){ return as_array(a, GenSeq<N>{}); }

template<typename T>
void print_signature(T&&)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main(){
  print_signature(as_array("hi"));
  auto arr = as_array("hi");
  std::cout << arr[0] << ", " << arr[1] << std::endl;
}