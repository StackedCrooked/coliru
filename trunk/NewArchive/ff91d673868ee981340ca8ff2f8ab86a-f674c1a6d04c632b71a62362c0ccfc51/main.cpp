#include <iostream>

int main()
{
    int a = 1;
    int* p = nullptr;
    int* q = &a;
    std::cout << (*(p | q)) << std::endl;
}