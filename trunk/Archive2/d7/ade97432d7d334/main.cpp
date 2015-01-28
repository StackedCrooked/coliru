// http://stackoverflow.com/questions/7124969/recursive-variadic-template-to-print-out-the-contents-of-a-parameter-pack
#include <string>
#include <typeinfo>
#include <iostream>

template <typename... Args>
struct Impl;

template <typename First, typename... Args>
struct Impl<First, Args...>
{
  static std::string name()
  {
    return std::string(typeid(First).name()) + " " + Impl<Args...>::name();
  }
};

template <>
struct Impl<>
{
  static std::string name()
  {
    return "";
  }
};

template <typename... Args>
std::string type_name()
{
    return Impl<Args...>::name();
}

int main()
{
  std::cout << type_name<int, bool, char, double>() << std::endl; // "i b c d"
  return 0;
}