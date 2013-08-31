#include <iostream>
constexpr bool is_prime_recursive(size_t number, size_t c)
{
  return (c*c > number) ? true : 
           (number % c == 0) ? false : 
              is_prime_recursive(number, c+1);
}
 
constexpr bool is_prime_func(size_t number)
{
  return (number <= 1) ? false : is_prime_recursive(number, 2);
}
template <bool b>
class A {
    static void print() {
                std::cout << b << std::endl;
        }
};      
int main() {
        A<is_prime_func(1000000007)>::print();
}