#include <iostream>
#include <cmath>

template <typename ValueType>
struct Round
{
    ValueType operator()(ValueType v) { return std::round(v); }
};

template <typename ValueType>
struct Floor
{
    ValueType operator()(ValueType v) { return std::floor(v); }
};

template <typename ValueType>
struct Ceil
{
    ValueType operator()(ValueType v) { return std::ceil(v); }
};

template <template<typename> class RoundingStrategy, typename ValueType> 
int convert(ValueType a, RoundingStrategy<ValueType> chosenRounding = RoundingStrategy<ValueType>())
{
    return chosenRounding(a);   
}

int main()
{
    std::cout << "Round:" << convert<Round>(4.5) << std::endl;
    std::cout << "Floor:" << convert<Floor>(4.5) << std::endl;
    std::cout << "Ceil:" << convert<Ceil>(4.5) << std::endl;
}
