#include <iostream>
#include <type_traits>
#include <utility>

constexpr int f(int a) { return a; } 

template<int N>
struct Test
{
    static constexpr auto value = N;    
};

int main()
{
    std::cout << Test<f(0)>::value;
}
