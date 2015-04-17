#include <iostream>
#include <limits>

int main()
{
    using limits = std::numeric_limits<double> ;
    
    std::cout << "minimum positive normalised value: " << limits::min() << '\n' 
              << "lowest normalised value: " << limits::lowest() << '\n' 
              << std::boolalpha << "sub-normal values supported? " << ( limits::has_denorm == std::denorm_present ) << '\n'
              << "for sub-mormal numbers, loss of precision is denormalization loss (not an inexact result)? " << limits::has_denorm_loss << '\n'
              << "smallest positive sub-normal value: " << limits::denorm_min() << '\n' ;
}
