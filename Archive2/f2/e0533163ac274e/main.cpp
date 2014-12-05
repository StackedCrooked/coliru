#include <iostream>
#include <string>
#include <vector>


int main()
{
    int x = 50;
    x += x--;
    
    std::cout << x << std::endl;
}
