#include <cstdint>
#include <iostream>
#include <string>

std::string rotate(std::string str)
{
    std::string result;
    result += str[str.length() - 1];
    result += str.substr(0, str.length() - 1);
    return result;
}


bool isRotated(std::string key, std::string test)
{
    if (key.length() == test.length()) {
        std::string tempStr = key;
        for(uint32_t i = 0; i < key.length(); i++) {
            tempStr = rotate(tempStr);
            if (tempStr.compare(test) == 0) { return true; }
        }
        return false;
    } else if (key.length() > test.length()) {
        return false;
    } else {
        uint32_t sizeDiff = test.length() - key.length();
        std::string tempStr = key;
        for(uint32_t offset = 0; offset < sizeDiff; offset++) {
            for(uint32_t i = 0; i < key.length(); i++) {
                tempStr = rotate(tempStr);
                if (test.find(tempStr, offset) != std::string::npos) { return true; }
            }
            tempStr = key;
        }
        return false;
    }
}


int main()
{
    std::cout << std::boolalpha;
    std::cout << isRotated("asdf", "fasd") << std::endl;      // rotated once     -> true
    std::cout << isRotated("asdf", "asfd") << std::endl;      // not possible     -> false
    std::cout << isRotated("asdf", "gasdf") << std::endl;     // offsetted        -> true
    std::cout << isRotated("asdf", "gfasd") << std::endl;     // offsetted        -> true
    std::cout << isRotated("asdf", "gasfd") << std::endl;     // offsetted        -> false
    std::cout << isRotated("dfdsafdsafd", "fd") << std::endl; // key is too large -> false
    return 0;
}
