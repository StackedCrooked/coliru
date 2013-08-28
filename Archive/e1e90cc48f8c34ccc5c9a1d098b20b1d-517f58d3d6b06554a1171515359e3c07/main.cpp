#include <iostream>
#include <tuple>

int main()
{
  std::tuple<int, long> t = std::make_tuple(5, 15L);
  
  int v;
  long d;
  std::tie(v,d) = t;
  
  std::cout << v << d;
}