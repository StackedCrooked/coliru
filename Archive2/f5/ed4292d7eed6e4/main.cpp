#include <iostream>

template<int...>
struct sum;

template<int i>
struct sum<i>
{
    static const int value = i;
};

template<int i,int ...tail>
struct sum<i,tail...>
{
    static const int value = i + sum<tail...>::value;
};

int main(void)
{
    std::cout << sum<1,2,3,4,5,6,7,8,9,10>::value << std::endl;

    return 0;
}