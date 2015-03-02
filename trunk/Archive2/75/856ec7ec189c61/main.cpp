#include <stdio.h>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    int32_t a = 0x11223344;
    char* bytes = (char*)&a;
    for (int i=0;i<4;i++) {
        std::cout<<bytes[i]<<"\n";
    };
}
