#include <meta/algorithm.h>
#include <tuple>
#include <utility>

namespace aux{
template<class T, unsigned... I1, unsigned... I2>
auto split(T const& t, meta::seq<I1...>, meta::seq<I2...>)
  -> decltype(std::make_pair(std::make_tuple(std::get<I1>(t)...), std::make_tuple(std::get<I2>(t)...)))
{
  return std::make_pair(std::make_tuple(std::get<I1>(t)...), std::make_tuple(std::get<I2>(t)...));
}
} // aux::

template<unsigned N, class T>
auto split_at(T const& t)
  -> decltype(aux::split(t, meta::gen_seq<N>{}, meta::sequence::GenOffsetSeq<std::tuple_size<T>::value - N, N>{}))
{
  return aux::split(t, meta::gen_seq<N>{}, meta::sequence::GenOffsetSeq<std::tuple_size<T>::value - N, N>{});
}

#include <type_traits>

int main(){
  auto t = std::make_tuple(42, 13.37, "hi", 3.14f);
  auto pt = split_at<2>(t);
  static_assert(std::is_same<decltype(pt.first), std::tuple<int, double>>(), "split 1");
  static_assert(std::is_same<decltype(pt.second), std::tuple<char const*, float>>(), "split 1");
}
