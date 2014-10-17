#include <type_traits>
#include <iostream>

template <typename T, bool Enable, typename... Args>
class AI;

template <typename T, typename... Args>
class AI<T, true, Args...>
{
public:
    AI() { std::cout << "true" << std::endl; } 
};

template <typename T, typename... Args>
class AI<T, false, Args...>
{
public:
    AI() { std::cout << "false" << std::endl; }
};

template <typename T, typename... Args>
using A = AI<T, T::value, Args...>;

int main()
{
    A<std::true_type, int, float, char>{};
    A<std::false_type, bool, double>{};
}
