#include <iostream>

template <typename T>
std::ostream& operator,(std::ostream& os, const T& arg)
{
    return os << ',' << arg;
}

int main()
{
    std::cout << 1, 2, 3 << '\n';
}
