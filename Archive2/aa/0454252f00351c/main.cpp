#include <stdio.h>
int main() {
    try{
        throw 0;
    }catch(int& i) {
        printf("int with value %d caught!\n", i);
    }
}
