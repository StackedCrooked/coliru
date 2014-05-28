#include <iostream>
#include <string.h>

void copyString(char stringToCopyTo[], char stringToCopy[]);

int main(){

    char string1[] = "Hello World!";
    char string2[80];

    copyString(string2, string1);

    std::cout << "String1: " << string1 << "\n";
    std::cout << "String2: " << string2 << "\n";

    return 0;
}

void copyString(char stringToCopyTo[], char stringToCopy[]){
    stringToCopyTo = stringToCopy;
}