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
 
    // string constructor using custom zero/one digits
    //std::string alpha_bit_string = "aBaaBBaB";
    //std::bitset<8> b6(alpha_bit_string, 0, alpha_bit_string.size(),
    //                  'a', 'B');         // [0,1,0,0,1,1,0,1]
 
    // char* constructor using custom digits
    //std::bitset<8> b7("XXXXYYYY", 8, 'X', 'Y'); // [0,0,0,0,1,1,1,1]

    std::cout << (b3 & b5 );
    
    return 0;
}