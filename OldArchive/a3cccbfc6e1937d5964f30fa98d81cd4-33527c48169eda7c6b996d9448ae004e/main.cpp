
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <type_traits>
#include<iostream>
#include<initializer_list>
#include<type_traits>

// template<typename T,typename Arg>
// constexpr bool is_initializer_list(Arg x)
// {
//     return std::is_same<Arg,std::initializer_list<T>>::value;
// }

template<typename Arg>
constexpr bool is_initializer_list(Arg x)
{
    return std::is_same<Arg,std::initializer_list<typename Arg::value_type>>::value;
}

int main()
{
  std::cout << std::boolalpha;
 
  std::initializer_list<int> x = {1,2,3,4,5};
  std::cout<<is_initializer_list(x) << '\n';
  
  auto e = {4,5,6};
 
  std::cout << is_initializer_list(e) << '\n';
  std::cout << is_initializer_list({'a','b','c'}) << '\n';
  std::cout << is_initializer_list("Hello World") << '\n';
  std::cout << is_initializer_list({7}) << '\n';

  static_assert(is_initializer_list(e), "is_initializer_liste)");
  return 0;
}

