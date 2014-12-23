#include <iostream>

template <typename T1, typename T2>
auto Bigger(T1 a1, T2 a2)
{
    return a2 > a1 ? a2 : a1;
}

int main()
{
    std::cout << Bigger(10, 1.1) << '\n'
              << Bigger(1.1, 10) << '\n';
}
