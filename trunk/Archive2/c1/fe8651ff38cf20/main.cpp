#include <iostream>

int main()
{
    if (const int x = 2) {
        std::cout << x << std::endl;
    }
    else {
        std::cout << x << ", wanker" << std::endl;
    }
}
