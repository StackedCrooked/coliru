template <int id>
struct IdToType {};

template<>
struct IdToType<1>
{
    typedef bool Type;
};

template<>
struct IdToType<2>
{
    typedef char Type;
};

template <int id>
typename IdToType<id>::Type getValue() 
{
    return 65;
}

#include <iostream>

int main()
{
    std::cout << getValue<1>() << std::endl;
    std::cout << getValue<2>() << std::endl;
}
