#include <iostream>
int main()
{
    int test1[1];
    int test2;
    std::cout << (sizeof(test1) == sizeof(test2));
}
