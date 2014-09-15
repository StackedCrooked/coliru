#include <iostream>
#include <tuple>

template<typename T>
struct Variable
{
    const char *name;

    constexpr Variable(const char* setName) : name(setName)
    {

    }
};

template<typename... Args>
class UniformBuffer;

template <typename... Args>
struct UniformBuffer<Variable<Args>...>
{
    using tuple = std::tuple<Variable<Args>...>;
    
    void print()
    {
        typename std::tuple_element<0, tuple>::type i("integer");
        typename std::tuple_element<1, tuple>::type d("double");
    }
};

int main()
{
    UniformBuffer<Variable<int>, Variable<double>> ub;
    ub.print();
}
