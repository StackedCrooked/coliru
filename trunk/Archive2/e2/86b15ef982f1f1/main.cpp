#include <iostream>

constexpr auto align(int value, int alignment, int remainder)
{
    return value + bool(remainder) * (alignment - remainder);
}

constexpr auto align(int value, int alignment)
{
    return align(value, alignment, value % alignment);
}


int main()
{
    std::cout << __LINE__ << ": " << align(1, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(2, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(3, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(4, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(5, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(6, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(7, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(8, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(9, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(10, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(11, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(12, 4) << std::endl;
    std::cout << __LINE__ << ": " << align(13, 4) << std::endl;
    
    std::cout << __LINE__ << ": " << align(1, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(2, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(3, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(4, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(5, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(6, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(7, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(8, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(9, 8) << std::endl;
    std::cout << __LINE__ << ": " << align(1, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(2, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(3, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(4, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(5, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(6, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(7, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(8, 16) << std::endl;
    std::cout << __LINE__ << ": " << align(9, 16) << std::endl;
}