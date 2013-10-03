#include <iostream>

int main()
{
    int p = 0;
    auto lambda = [&p] {
        std::cout << &p << std::endl;
    };

    lambda(); // 0x7fff78e6b7e0
}