#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct Variable
{
    char *name;

    constexpr Variable(char *setName) : name(setName)
    {

    }
};

template<typename First, typename... Args>
class UniformBuffer;

template<typename First, typename... Args>
class UniformBuffer<Variable<First>,Variable<Args>...>
{
    void f();
};

int main()
{
    UniformBuffer<Variable<int>,Variable<double>,Variable<float>> ub;    
    ub.f(); // provoke error to show the deduced types First and Args...
}
