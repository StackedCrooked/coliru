#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i;
    for(i=1; i<argc; i++) 
    {
        printf("%s\n", argv[i]);
    }
    printf("\n");
    char *chant;
    chant = strstr(argv[1], argv[2]);
    printf("The subtring is: %s\n", chant);
    if(chant==NULL)
    {
       printf("good bye");
    }
    return 0;
} 
