#include <iostream>
 
int main()
{
    int x = 2; // change this and see the results
    if (x == 2) {
        std::cout << "x is equal to 2\n";
    }
 
    int y = 17;
    if (x == 3) {
        y = 4;
    }
    std::cout << "y: " << y << "\n";
 
    if (y == 17) {
        std::cout << "y is equal to 17\n";
    } else {
        std::cout << "y is not equal to 17\n";
    }
}