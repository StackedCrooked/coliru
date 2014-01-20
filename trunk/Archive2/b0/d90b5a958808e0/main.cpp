#include <iostream>

int main() {
    int x = 0x7ffffffe;
    int y = 0x7ffffffd;
    std::cout << x << " " << y << std::endl;  
    if ((float) x == (float) y)
        std::cout << "float lost precision" << std::endl;
    if ((double) x == (double) y)
        std::cout << "double lost precision" << std::endl;
}
