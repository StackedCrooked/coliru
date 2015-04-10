#include <iostream>

class A
{
};

class B
{
    B& operator = (const B&) = delete;
};

template <class...>
using void_t = void;

template <class, class = void>
struct is_copy_assignable : std::false_type {};

template <class T, void_t<decltype( std::declval<T&> () = std::declval<const T&> () )>>
struct is_copy_assignable : std::is_same<T&, decltype( std::declval<T&> () = std::declval<const T&> () )> {};

int main()
{
  std::cout << is_copy_assignable<A>::value << std::endl;
  std::cout << is_copy_assignable<B>::value << std::endl;
}
