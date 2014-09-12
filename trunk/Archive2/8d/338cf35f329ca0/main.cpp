#include <vector>
#include <iostream>

template<int... Is>
struct integer_sequence { };

template<int N, int... Is>
struct make_integer_sequence : make_integer_sequence<N - 1, N - 1, Is...> { };

template<int... Is>
struct make_integer_sequence<0, Is...> : integer_sequence<Is...> { };
    
template<int... Is>
void foo(integer_sequence<Is...> is) 
{
    std::vector<int> v{Is...};
    for (auto x : v) { std::cout << x << " "; }
}
    
int main()
{
    foo(make_integer_sequence<3>());
};