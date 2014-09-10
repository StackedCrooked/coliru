#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <stdexcept>

unsigned getNumber(char input) {
    if (input>='0' && input <= '9')
        return input-'0';
    if (input>='A' && input <= 'Z')
        return input-'A'+10;
    if (input>='a' && input <= 'z')
        return input-'a'+10;
    return ~0u;
}


double  getBase10 (const std::string& number, int CurrentBase){
    double converted = 0.0;
    double scale = 1.0;
    unsigned i;
    for (i =0; i < number.size(); i++){
        unsigned digit = getNumber(number[i]);
        if (digit == ~0u) break;
        converted = converted*CurrentBase + digit;
    }
    if (number[i] == '.') {
        for (++i; i < number.size(); i++){
            unsigned digit = getNumber(number[i]);
            if (digit == ~0u) break;
            converted = converted*CurrentBase + digit;
            scale *= CurrentBase;
        }
    }
    if (i<number.size())
        throw std::runtime_error("invalid character "+std::string(1,number[i]));
    
    double result = converted / scale;
    return result;
}


int main()
{
    std::cout << getBase10("4",10) << '\n';
    std::cout << getBase10("14",10) << '\n';
    std::cout << getBase10("14.",10) << '\n';
    std::cout << getBase10("14.6",10) << '\n';
    std::cout << getBase10("14.67",10) << '\n';
    std::cout << getBase10("4",8) << '\n';
    std::cout << getBase10("14",8) << '\n';
    std::cout << getBase10("14.",8) << '\n';
    std::cout << getBase10("14.6",8) << '\n';
    std::cout << getBase10("14.67",8) << '\n';
}
