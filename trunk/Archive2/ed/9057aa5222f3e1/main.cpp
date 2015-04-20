#include <iostream>
#include <stdio.h>

void printMarcAge(unsigned int ageGuess)  {
    unsigned int x = 0xBADC0DE;
    unsigned int offset = 0x1;
    unsigned int marcAge = (x % ageGuess) - offset;
    printf("My age: %d \n", marcAge);
}

int main() {
    printMarcAge(0x42);
}
