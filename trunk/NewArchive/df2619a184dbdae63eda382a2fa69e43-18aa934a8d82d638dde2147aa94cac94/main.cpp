#include <bitset>
#include <string>
#include <iostream>

int main() {
    std::string bits;
    bits.push_back('1');
    bits.push_back('0');
    bits.push_back('1');
    bits.push_back('1');
    bits.push_back('1');
    std::bitset<8> bitset(bits);
    std::cout << bitset.to_string();

}