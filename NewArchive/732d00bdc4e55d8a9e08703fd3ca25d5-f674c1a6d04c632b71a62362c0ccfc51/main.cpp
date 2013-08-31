#include <iostream>
#include <string>



char (*cp)[10] = NULL;  //pointer to an array of 10
char *cpa[10] = {NULL};  //array of 10 char pointers
int main()
{
    int a;
    char c;
    float f;
    double d;
    
    printf("%u %u %u %u\n", sizeof(a), sizeof(c), sizeof(f), sizeof(d));
    printf("%u", (char*)(&d+1) - (char*)&d);
    
    cp = (char(*)[10])malloc(10);
    return 0;
}
