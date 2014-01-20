#include <iostream>


int main()
{
    int a[2][3];
    int* begin = a[0];
    int* end = begin + sizeof(a);
    std::cout << (end - begin) << std::endl;
}