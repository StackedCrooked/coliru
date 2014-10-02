#include <stdio.h>      /* FILE, fopen, fclose, fprintf */
#include <stdlib.h>     /* abort */
 
int main(void) 
{
    FILE *fp = fopen("data.txt","r");
    if (fp == NULL) {
       fprintf(stderr, "error opening file data.txt in function main()\n");
       abort();
    }
 
    /* Normal processing continues here. */
    fclose(fp);
    printf("Normal Return\n");
    return 0;
}