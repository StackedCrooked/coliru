#include <vector>
#include <iostream>

template<typename T, T... Is>
struct integer_sequence { };

template<typename T, std::size_t N, std::size_t... Is>
struct make_integer_sequence : make_integer_sequence<T, N - 1, N - 1, Is...> { };

template<typename T, std::size_t... Is>
struct make_integer_sequence<T, 0, Is...> : integer_sequence<T, Is...> { };
    
template<typename T, std::size_t... Is>
void foo(integer_sequence<T, Is...> is) 
{
    std::vector<int> v{Is...};
    for (auto x : v) { std::cout << x << " "; }
}
    
int main()
{
    foo(make_integer_sequence<int, 3>());
};