#include <iostream>
#include <cstdio>
 
int main()
{
    std::cout.sync_with_stdio(false);
    std::cout << "a\n";
    std::printf("b\n");
    std::cout << "c\n";
}