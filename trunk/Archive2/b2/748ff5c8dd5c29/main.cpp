#include <boost/variant.hpp>

#include <iostream>
#include <string>
#include <type_traits>

template<typename T, typename Variant>
constexpr std::size_t variant_type_index()
{
  return std::declval<Variant>(std::declval<T>()).which();
}

int main()
{
  using myvariant = boost::variant<int, std::string, double>;
  
  std::cout << variant_type_index<double, myvariant>()<< '\n';
}