#include <stdlib.h>
#include <stdio.h>

void Error(char* s)
{
    printf(s);
    return;
}

int main()
{
    Error("Could not allocate the memory\n");
    Error("Quitting....\n");
    
    return 0;
}