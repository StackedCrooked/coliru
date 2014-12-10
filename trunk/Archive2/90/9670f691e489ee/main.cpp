#include <iostream>

template <typename R, typename T1, typename T2>
R add(T1 t1, T2 t2)
{
    R val = t1 + t2;
    return val;
}

int main()
{
    double a = 12.5;
    int b = 4;
    std::cout << add<double>(a, b) << std::endl;
}
