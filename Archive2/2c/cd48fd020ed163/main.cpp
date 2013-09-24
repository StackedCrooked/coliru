#include <iostream>
#include <string>
#include <vector>

int main()
{
    int a = 5;
    int b = *(&a) + 1;
    std::cout << a << " " << b << std::endl;
}
