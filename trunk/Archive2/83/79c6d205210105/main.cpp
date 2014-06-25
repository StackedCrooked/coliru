#include <iostream>
#include <type_traits>

template <class T, class U>
auto min1(T x, U y)
{ return x < y ? x : y; }

template <class T, class U, 
          class = std::enable_if_t<std::is_integral<T>::value &&
                                   std::is_integral<U>::value>>
auto min2(T x, U y)
{ return x < y ? x : y; }

struct foo {};

int main()
{
   min1(foo{}, foo{}); // error - invalid operands to <
   min1(10, 20);
   
   min2(foo{}, foo{}); // no matching function min2
   min2(10, 20);
}
