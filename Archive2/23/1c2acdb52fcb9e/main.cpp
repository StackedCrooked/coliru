#include <stdio.h>

typedef struct
{
    int a;
    int b;
    int c;
} myStruct;

int main()
{
    myStruct aStruct;
    aStruct.a = 1;
    aStruct.b = 2;
    aStruct.c = 3;
    
    int *aBadBoyPointer = &aStruct.a;
    
    printf("%i %i %i", *(aBadBoyPointer), *(++aBadBoyPointer), *(++aBadBoyPointer));
}