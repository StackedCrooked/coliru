#include <cstdio>
#include <type_traits>

template<typename T>
constexpr bool is_prime_helper(T n, T div)
{
    return (div*div > n) ? true :
        (n % div == 0) ? false :
            is_prime_helper(n, div+2);
}
 
template<typename T>
constexpr
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_prime(T n)
{
    return (n < 2) ? false :
        (n == 2) ? true :
            (n % 2 == 0) ? false :
                is_prime_helper(n, 3);
}

int main(void)
{
   static_assert(is_prime(1000000006), "...");  // Computed at compile-time
  // int i = 11;
  // int j = is_prime_func(i)); // Computed at run-time
}