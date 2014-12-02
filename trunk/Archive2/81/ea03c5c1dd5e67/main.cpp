#include<stdio.h>

char* SumCharsAndDigits(const char* str){
    int i = 0;
    int count;
    while (str[i] != '\0'){
        count += str[i]
    }
    return count + 64
}

int main(int args, char *argv[]) {
    const char input = "HELLO";
    printf("%d",SumCharsAndDigits(input));
    return 0;
}
