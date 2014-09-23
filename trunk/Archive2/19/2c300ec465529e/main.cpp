#include <iostream>

int main()
{
    int x = 0;
    do
    {
        std::cout << x << std::endl;   
    } while(x++ < 10);
    
    std::cout << std::endl;
    
    do
    {
        int y = 0;
        std::cout << y << std::endl;   
    } while(y++ < 10); // even if this did compile, it'd be an infinite loop
}
