#include <iostream>

int main()
{
    int x = 0;
    
    switch(x) {
        default:
            std::cout << "default" << std::endl;
            break;
        case 3:
            std::cout << 3 << std::endl;
            break;
        case 2:
            std::cout << 2 << std::endl;
            break;
        case 1:
            std::cout << 1 << std::endl;
            break;
    }
}

