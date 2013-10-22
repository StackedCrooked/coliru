#include <bitset>
#include <string>
#include <iostream>

int main() 
{
    // empty constructor
    //std::bitset<8> b1; // [0,0,0,0,0,0,0,0]
 
    // unsigned long long constructor
    //std::bitset<8> b2(42); // [0,0,1,0,1,0,1,0]
 
    // string constructor
    //std::string bit_string = "110010";
    std::bitset<8> b3("110010");       // [0,0,1,1,0,0,1,0]
    std::bitset<8> b4("10011001");    // [0,0,0,0,0,0,1,0]
    std::bitset<8> b5("101010"); // [0,0,0,0,0,0,0,1]
 

    std::cout << (b3 & b5 ) << std::endl;
    std::cout << (b3 | b5 ) << std::endl;
    std::cout << (b3 ^ b5 ) << std::endl;
    
    std::cout << b3 << "\t all: " << b3.all() << "\t any: " << b3.any() << "\t none: " << b3.none()  << std::endl;
    
    std::cout << b3.test(0) << " " << b3.test(5) << std::endl;
    
    return 0;
}