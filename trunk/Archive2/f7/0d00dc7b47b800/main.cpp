#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>

float power (float val, int pow) {
    if (val==0) return 0;
    if (pow==0) return 1;
    float result = val;
    for (int i=1; i<pow; i++) {
        result*=result;
    };
    return result;
};

int ToDec(std::string val, int base) {
    std::string string = val;
    int result = 0;
    int array[255];
    for (int i=string.length()-1; i>=0; i--) {
        const char chr[1] = {string.at(i)};
        array[string.length()-1-i] = atoi(chr);
    };
    for (int i=0; i<string.length(); i++) {
       result+=array[i]*power(base, i);
    };
    
    return result;
};

std::string ToBase(std::string val, int base) {
    std::string result = "";
    int number = stoi(val);
    
    int array[255];
    int i=0;
    while (number>base-1) {
        array[i] = number%base;
        number/=base;
        i++;
    };
    char string[1];
    for (int j=0; j<i; j++) {
       sprintf(string, "%d", array[j]);
       result+=string[0];
    };
    
    return result;
};

int main()
{
    std::cout<<ToBase("220", 2);//ToDec("220", 16);
}

