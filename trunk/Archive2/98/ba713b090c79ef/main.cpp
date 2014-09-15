#include <type_traits>
#include <iostream>

template<class From, class To, class Value>
struct convert
{
    static Value apply(Value value)
    {
        using tag = std::integral_constant<bool, std::is_same<From, To>::value>;
        return _apply(value, tag{});
    }
    
private:
    static Value _apply(Value value, std::true_type)
    {
        std::cout << "Same" << std::endl;
        return value;
    }
    
    static Value _apply(Value value, std::false_type)
    {
        std::cout << "Not the same" << std::endl;
        return value;
    }
};

int main()
{
    convert<int, int, float>::apply(3.14f);
    convert<int, float, float>::apply(3.14f);
}
