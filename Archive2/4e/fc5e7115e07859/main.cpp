#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <array>
#include <stdint.h>

const int32_t NumberOfDecimals = 6;

std::string decimalToString(int64_t number){
    std::string numberStr = std::to_string(number);
    int32_t zerosToAdd = NumberOfDecimals - numberStr.length() + 1;
    while(zerosToAdd > 0){
        numberStr = "0" + numberStr;
        zerosToAdd--;
    }
   numberStr.insert((numberStr.length()-NumberOfDecimals), ",");
   return numberStr;
}


int main() {

    std::cout << decimalToString(123456) << std::endl;
    std::cout << decimalToString(123456789) << std::endl;
     std::cout << decimalToString(12) << std::endl;
    
}
