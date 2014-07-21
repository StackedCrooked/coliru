#include <iostream>

void *p = operator new(0);

int main()
{
    std::cout << p;
}