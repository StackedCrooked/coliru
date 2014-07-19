#include <iostream>

int main()
{
    int a = 1024;
    char* ar = reinterpret_cast<char*>(&a);
    int b = *((int*)ar);
    std::cout << b;
    return 0;
}