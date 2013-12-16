#include <iostream>
#include <type_traits>
 
template <typename T, typename U>
struct decay_equiv : 
    std::is_same<U, typename std::decay<T>::type>::type 
{};
 
int main()
{
    std::cout << std::boolalpha << decay_equiv<int, int>::value << '\n';
    std::cout << std::boolalpha << decay_equiv<int&, int>::value << '\n';
    std::cout << std::boolalpha << decay_equiv<int&&, int>::value << '\n';
    std::cout << std::boolalpha << decay_equiv<const int&, int>::value << '\n';
    std::cout << std::boolalpha << decay_equiv<int[2], int*>::value << '\n';
    std::cout << std::boolalpha << decay_equiv<int(int), int(*)(int)>::value << '\n';
}