const double i = 25;

template <class T>
static constexpr T SEC3 = i;

#include <iostream>

int main()
{
    std::cout << SEC3<int>;
}