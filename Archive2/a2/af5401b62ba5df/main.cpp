#include <stdio.h>
#include <iostream>

int main() {
    for (int i = 0; i < 100; ++i) {
        printf("%c\n", (i + 0x30));   
    }
    
}