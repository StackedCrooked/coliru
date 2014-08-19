#include <cstdint>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

char bin2hex[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
};

int convertBase(char* dest, int maxDestLength, const char* inputInBase10)
{
    std::string result;
    std::vector<uint32_t> bigNum(5, 0); // 5 unsigned ints, zero initialized
    int inStrSize = strlen(inputInBase10);

    for (int inStrIndex = 0; inStrIndex < inStrSize; ++inStrIndex) {
        // get character from string and convert it to decimal
        if (inputInBase10[inStrIndex] == 0) { break; } // reached end of string, just in case
        uint32_t decValue = (uint32_t)inputInBase10[inStrIndex] - 48;

        // add value to bigNum
        uint32_t offset = 0;
        uint64_t tempLargeInt = bigNum[0] + decValue;

        // and carry value
        while (tempLargeInt > 0) {
            bigNum[offset] = tempLargeInt & 0xFFFFFFFF;
            tempLargeInt >>= 32;
            offset++;
            if (offset >= bigNum.capacity()) { bigNum.push_back(0); }
            tempLargeInt += bigNum[offset];
        }

        // if we aren't at the end of the input string, multiply bignum by 10
        if (inStrIndex + 1 != inStrSize) {
            offset = 0;
            tempLargeInt = (uint64_t)bigNum[offset] * 10;
            while (tempLargeInt > 0) {
                bigNum[offset] = tempLargeInt & 0xFFFFFFFF;
                tempLargeInt >>= 32;
                offset++;
                if (offset >= bigNum.capacity()) { bigNum.push_back(0); }
                tempLargeInt = tempLargeInt + ((uint64_t)bigNum[offset] * 10);
            }
        }
    }

    // produce hexadecimal string
    for (int32_t bigNumIndex = bigNum.size() - 1; bigNumIndex >= 0; --bigNumIndex) {
        //std::cout << "bigNum[" << bigNumIndex << "]: " << bigNum[bigNumIndex] << std::endl;
        uint32_t value = bigNum[bigNumIndex];
        result += bin2hex[(value >> 28) & 0xF];
        result += bin2hex[(value >> 24) & 0xF];
        result += bin2hex[(value >> 20) & 0xF];
        result += bin2hex[(value >> 16) & 0xF];
        result += bin2hex[(value >> 12) & 0xF];
        result += bin2hex[(value >>  8) & 0xF];
        result += bin2hex[(value >>  4) & 0xF];
        result += bin2hex[(value >>  0) & 0xF];
    }

    // copy result string to destination string
    uint32_t resIndex = 0, destIndex = 0;
    while (result[resIndex] == '0') { resIndex++; } // skip leading zeros
    while (resIndex < result.length()) {
        dest[destIndex++] = result[resIndex++];
    }
    dest[destIndex] = 0;
    return strlen(dest);
}

int main()
{
    char thing[100];
    int resultSize;
    std::string resultString;

    resultSize = convertBase(thing, 50, "1045");
    resultString = thing;
    std::cout << "inputInBase10: " << "1045";
	std::cout << "\ndest: " << resultString;
	std::cout << "\nreturn value: " << resultSize;
	std::cout << std::endl << std::endl;

    resultSize = convertBase(thing, 50, "123487032174829820348320429437483266812812");
    resultString = thing;
    std::cout << "inputInBase10: " << "123487032174829820348320429437483266812812";
	std::cout << "\ndest: " << resultString;
	std::cout << "\nreturn value: " << resultSize;
	std::cout << std::endl << std::endl;


    return 0;
}
