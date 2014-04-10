
#include <iostream>
#include <unordered_map>

std::unordered_map<unsigned int, std::unordered_map<unsigned int, unsigned char>> data;

int main() {
    data[232432][234234] = 2;
    data[2][2] = 1;
    std::cout << data[232432][234234] << std::endl;
    //std::cout << data[3][3] << std::endl;
    //std::cout << data[232432][1] << std::endl;
    std::cout << data[2][2] << std::endl;
}

