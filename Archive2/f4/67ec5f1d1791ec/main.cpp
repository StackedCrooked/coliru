#include <iostream>
#include <iterator>

int main()
{
    auto x = 0;
    for (auto c : "hello") ++x;
    std::cout << x;
}