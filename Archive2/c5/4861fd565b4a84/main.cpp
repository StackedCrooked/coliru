#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char * names[10];
    
    names[0] = (char *)malloc(15);
    names[1] = (char *)malloc(15);

    strcpy(names[0], "yyyyyyyyyyyyyyyyyyyyyyyyyyyy"); // 25+ 
    strcpy(names[1], "xxxxxxxxx");
    printf("%s\n", names[0]);
    printf("%s\n", names[1]);
}
