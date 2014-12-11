#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    char*name;
    char*surname;
    
    scanf_s("%s %s", name,surname); //_s bec of microsoft visual stduio. two seperate scanf_s work
    printf("%s",strcat(name,surname);
}

