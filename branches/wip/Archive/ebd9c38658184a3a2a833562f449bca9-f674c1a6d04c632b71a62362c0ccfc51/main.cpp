#include <iostream>

int main()
{
    int a = 1;
    int* p = nullptr;
    int* q = &a;
    std::cout << *reinterpret_cast<int *>(reinterpret_cast<long>(p) | reinterpret_cast<long>(q)) << std::endl;
}