#include <cstring>
#include <iostream>
 
int main()
{
    int a[20];
    std::memset(a, 0, sizeof(a));
    for (int i : a)
        std::cout << i;
    std::cout << '\n';
}