#include <iostream>
#include <cstring>
 
int main()
{
    int a[20];
    std::memset(a, 0, sizeof(a));
    for (int ai : a) std::cout << ai;
}