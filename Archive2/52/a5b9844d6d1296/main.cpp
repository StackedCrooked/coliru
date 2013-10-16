#include <iostream>
#include <tuple>

template <int N, typename T>
struct A { };

template <typename Tuple>
double result(const Tuple& t, const A<0, typename std::tuple_element<0, Tuple>::type>& a)
{
  return 0;
}

template <typename Tuple, int N>
typename std::enable_if<N == std::tuple_size<Tuple>::value-1, double>::type
result(const Tuple& t, const A<N, typename std::tuple_element<N, Tuple>::type>& a)
{
  return 1;
}

template <typename Tuple, int N>
typename std::enable_if<N != std::tuple_size<Tuple>::value-1, double>::type
result(const Tuple& t, const A<N, typename std::tuple_element<N, Tuple>::type>& a)
{
  return 0.5;
}

int main()
{
  auto a = std::make_tuple(0, 1, 2., 3., 4);
  std::cout << result(a, A<0,int>()) << std::endl;
  std::cout << result(a, A<2,double>()) << std::endl;
  std::cout << result(a, A<4,int>()) << std::endl; // Fails if uncommented
  return 0;
}