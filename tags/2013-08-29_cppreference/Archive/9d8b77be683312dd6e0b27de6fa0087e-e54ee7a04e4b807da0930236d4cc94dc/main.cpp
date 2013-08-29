#include <stdio.h>

bool parity(int a){
    a ^= a << 8;
    a ^= a << 4;
    a ^= a << 2;
    a ^= a << 1;
    return (a&1)==0;
}

int main(){

    printf(
        "%s\n%s",
        parity(1)?"true":"false",
        parity(2)?"true":"false"
    );
}
