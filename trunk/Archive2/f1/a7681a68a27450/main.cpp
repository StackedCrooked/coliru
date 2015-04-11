#include <iostream>

class A
{
};

class B
{
  B& operator = (const B&) = delete;
};

template<class T>
using copy_assignment_t
= decltype(std::declval<T&>() = std::declval<T const&>());

template<class T, class Enable = void>
struct is_copy_assignable : std::false_type {};

template<class T>
struct is_copy_assignable<T, typename std::enable_if<std::is_same<copy_assignment_t<T>,T&>::value>::type>
: std::true_type {};

int main()
{
  std::cout << is_copy_assignable<A>::value << std::endl;
  std::cout << is_copy_assignable<B>::value << std::endl;
}
