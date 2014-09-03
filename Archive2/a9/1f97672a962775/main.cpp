#include <iostream>

template <typename T>
const int value = value<int>;

int main()
{
    std::cout << value<int> << std::endl;
}
