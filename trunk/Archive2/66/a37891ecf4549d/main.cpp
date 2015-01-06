#include <iostream>

int main()
{
    // !?!?!???!?!?!?!?!?!??!??/
    std::cout << "Hello World" << std::endl;
    std::cout << "Goodbyte World" << std::endl;
    
    int the_hell_is_this[2:> = {0, 1};
    int the_hell_is_that[2:> = {2, 3};
    
    the_hell_is_this[2:> = the_hell_is_that<:2];
    
    for(int i = 0; i != 2; ++i)
    {
        std::cout << the_hell_is_this[i:> << std::endl;
        std::cout << the_hell_is_that[i:> << std::endl;
    }
}