#include <iostream>
 
int main()
{
    std::cout << "x:";
 
    int x = 0;
    do {
        ++x;
        std::cout << " " << x;
    } while (x < 5);
 
    std::cout << "\n" << "y:";
 
    int y = 1729;
    do {
        ++y;
        std::cout << " " << y;
    } while (y < 5);
}