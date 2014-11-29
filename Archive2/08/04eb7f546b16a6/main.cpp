#include <iostream>
#include <type_traits>

int main()
{
    int n = 5;
    int& i = n;
    std::cout << std::is_same<int&, decltype(i)>::value;
}