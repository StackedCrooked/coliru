#include <iostream>

unsigned long long  readAndSkipLong(char* b)
{
    unsigned long long ret = 0;
    for(int i=0; i<8; ++i) 
        ret = (ret<<8) | (unsigned char)b[i];
    return ret;
}

int main() {
    char b[8] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
    unsigned long long v = readAndSkipLong(b);
    std::cout << std::hex << v;
}