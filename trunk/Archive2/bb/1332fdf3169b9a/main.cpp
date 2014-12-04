#include <iostream>
#include <string>
#include <vector>

int main()
{
    int i = 0;
    std::cout << i;
    [=]() mutable { std::cout << ++i; }();
    std::cout << i;
}
