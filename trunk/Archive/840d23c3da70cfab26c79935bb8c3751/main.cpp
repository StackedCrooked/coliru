#include <iostream>
#include <thread>

template<typename T>
using uT = const T;
uT foo (T t)
{
    return const_cast<uT>(t);
}

int main()
{
    return 0;
}