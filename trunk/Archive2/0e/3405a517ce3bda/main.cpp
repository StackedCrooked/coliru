#include <iostream>
#include <utility>
 
void foo (int &&i)
{
    i = 6;
}
 
int main()
{
    int a = 5;
    std::cout << a << std::endl;
    foo (std::move(a));
    std::cout << a << std::endl;
    return 0;
}