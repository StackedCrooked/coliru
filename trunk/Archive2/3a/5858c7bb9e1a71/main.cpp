#include <iostream>
#include <type_traits>

template <typename T, typename U>
struct foo
{
    typedef decltype(true ? std::declval<T>() : std::declval<U>()) type;
};

int main() 
{
  std::cout << std::is_same<int, foo<int, short>::type>::value << std::endl;
}