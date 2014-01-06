#include <iostream>
#include <string>
#include <vector>

int main()
{
    int i = 1;
    int a = i++ + ++i;
    std::cout << a;
}
