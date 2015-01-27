#include <stdio.h>

const char *string_of_digit(unsigned int digit) {
    switch (digit) {
        case 0:  return "zero";
        case 1:  return "one";
        case 2:  return "two";
        case 3:  return "three";
        case 4:  return "four";
        case 5:  return "five";
        case 6:  return "six";
        case 7:  return "seven";
        case 8:  return "eight";
        case 9:  return "nine";
        default: return "?";
    }
}

int double_digit(unsigned int digit) {
    int sum = 0;
    switch (digit) {
        case 9: sum += 2;
        case 8: sum += 2;
        case 7: sum += 2;
        case 6: sum += 2;
        case 5: sum += 2;
        case 4: sum += 2;
        case 3: sum += 2;
        case 2: sum += 2;
        case 1: sum += 2;
        default: break;
    }
    return sum;
}

int main(void) {
    for (int i = 0; i < 10; ++i) {
        printf("%s\n", string_of_digit(i));
    }
    
    for (int i = 0; i < 10; ++i) {
        printf("%d\n", double_digit(i));
    }
    
    return 0;
}