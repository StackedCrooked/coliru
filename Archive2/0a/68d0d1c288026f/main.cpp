#include <iostream>

int main()
{
    auto H = 8; auto W = 8;
    auto black = "\u25a0";
    auto white = "\u25a1";
    
    for (auto i = 0; i < H; ++i) {
        for (auto j = 0; j < W; ++j) {
            std::cout << ( ((i + j) % 2 == 0)? white : black);
        }
        std::cout << std::endl;
    }
}