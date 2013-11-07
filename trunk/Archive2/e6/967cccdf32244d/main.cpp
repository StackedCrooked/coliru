#include <iostream>
#include <array>

template <std::size_t W, std::size_t H>
struct Block
{
    std::array<std::array<int, W>, H> block;
};

int main() 
{
    Block<3, 2> b1 {1, 2, 3, 4, 5, 6};
    Block<3, 2> b2 {{1, 2, 3, 4, 5, 6}};
    Block<3, 2> b3 {{{ {{1, 2,3}}, {{4,5,6}} }}}; 

    (void)b1;
    (void)b2;
    (void)b3;
    std::cout << "okay" << std::endl;
}