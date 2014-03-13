#include <iostream>
#include <cmath>

template <typename ValueType>
struct Round
{
    static ValueType convert(ValueType v) { return std::round(v); }
};

template <typename ValueType>
struct Floor
{
    static ValueType convert(ValueType v) { return std::floor(v); }
};

template <typename ValueType>
struct Ceil
{
    static ValueType convert(ValueType v) { return std::ceil(v); }
};

template <template<typename> class RoundingStrategy, typename ValueType> 
int convert(ValueType a)
{
    return RoundingStrategy<ValueType>::convert(a);   
}

int main()
{
    std::cout << "Round:" << convert<Round>(4.5) << std::endl;
    std::cout << "Floor:" << convert<Floor>(4.5) << std::endl;
    std::cout << "Ceil:" << convert<Ceil>(4.5) << std::endl;
}
