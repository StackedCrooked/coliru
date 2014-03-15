#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;
#include <stdio.h>
//compile :
//> gcc -o checkEndian checkEndian.c
 
void EndianTest(){
 
    unsigned int i =0;
 
    int v = 1;
    //v += 255;
    v += 65535;
    char * c = (char *) &v;
 
    printf("sizeof(char): %ld\n", sizeof(char));
    printf("sizeof(int):  %ld\n", sizeof(int));
    printf("Given number %d represented in char array:\n", v);
    printf("char array: [");
    for(i = 0; i < sizeof(int) -1;  i++){
        printf("%u:", c[i]);
    }
    printf("%u", c[sizeof(int)-1]);
    printf("]\n");
}
 
int IsBigEndian(){
 
    int result = 0;
    int v = 1;
 
    char * c = (char *) &v;
    if( (*c) == 0){
        result = 1;
    }
    return result;
}
 
int main(int argc, char ** argv)
{
    if (IsBigEndian() == 1){
        printf("This is big endian.\n");
    }
    else{
        printf("This is little endian.\n");
    }
    EndianTest();
    return 0;
}