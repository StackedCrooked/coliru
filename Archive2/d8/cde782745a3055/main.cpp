#include <iostream>
#include <string>
#include <vector>

int * foo(){
    int y=12;
    return &y;
}

int main()
{
    int x = 4;
    int y = 100;
    int &r = x;
    r = y;
    r++;
    
    std::cout << r << std::endl;
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    
    int *xp = foo();
    
    
    std::cout << *xp << std::endl;
}
