#include <iostream>
#include <cmath>

const unsigned screen_x = 1024;
const unsigned screen_y = 1024;

float calc_block_side(unsigned desired_x, unsigned desired_y)
{
    //desired_x * desired_y = number of blocks
    //block_side^2 = area of one block
    //block_side^2 * desired_x * desired_y = area of all the blocks; has to match the area of the screen
    
    //so we can say, screen_x * screen_y = block_side^2 * desired_x * desired_y
    //and block_side is then sqrt((screen_x*screen_y)/(desired_x*desired_y))
    
    return std::sqrt((float)(screen_x*screen_y)/(desired_x*desired_y));
}

int main()
{
    std::cout << calc_block_side(7, 8) << "\n";
}