#include <iostream>
#include <tuple>

template<int... N>
auto f()
{
    return std::make_tuple(7 + N...);
};

int main()
{
  auto var = f<0,2,5>();
  std::cout << std::get<0>(var) << " " << std::get<1>(var) << " " << std::get<2>(var) << "\n";
}