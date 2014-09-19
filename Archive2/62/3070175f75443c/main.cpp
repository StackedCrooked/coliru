#include <vector>
#include <iostream>

std::vector<int> a(2, 2);

int main()
{
    decltype(a)::value_type b = a[0];
    std::cout << b;
}