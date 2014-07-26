#include <iostream>
#include <string>
#include <cstdint>
#include <netinet/in.h>

std::string toBinary(const unsigned char* c_ptr, const std::size_t &bytes)
{
    unsigned char bitPattern;
    std::string binaryString("");
    for (std::size_t byte(0); byte < bytes; ++ byte) {
        bitPattern = 0x80;    // 10000000 in binary
        for (unsigned int bit = 0; bit < 8; ++ bit) {
            if ((bitPattern & *(c_ptr + byte)) > 0)    // (c_ptr + byte) is the current address.
                binaryString += "1";
            else
                binaryString += "0";
            bitPattern >>= 1;
        }
    }
    return binaryString;
}

int main()
{
    std::uint16_t variable_host = 45;  // host byte order
    const unsigned char *c_ptr = reinterpret_cast<const unsigned char*>(&variable_host);
    std::cout << toBinary(c_ptr, sizeof(variable_host)) << std::endl;

    // http://www.beej.us/guide/bgnet/output/html/multipage/htonsman.html
    std::uint16_t variable_nw = htons(variable_host) ;  // netwok byte order
    c_ptr = reinterpret_cast<const unsigned char*>(&variable_nw);
    std::cout << toBinary(c_ptr, sizeof(variable_nw)) << std::endl;
}
