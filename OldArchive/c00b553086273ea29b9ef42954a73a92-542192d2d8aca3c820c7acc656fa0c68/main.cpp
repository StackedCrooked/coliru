
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

int main()
{
    int a=50000, b=50000;
    std::cout << a * b << std::endl;
    std::cout << (long long) a * (long long) b << std::endl;
    std::cout << a * (long long) b << std::endl;
}