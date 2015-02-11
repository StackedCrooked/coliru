#include <iostream>


inline int UniqueNumber()
{
    static int n;
    return n++;
}


template<typename T>
int TypeId()
{
    static int index = UniqueNumber();
    return index;
}


int main()
{
    std::cout << TypeId<int>() << ' ' << TypeId<short>() << ' ' << TypeId<char>() << std::endl;
    std::cout << TypeId<int>() << ' ' << TypeId<short>() << ' ' << TypeId<char>() << std::endl;
}
