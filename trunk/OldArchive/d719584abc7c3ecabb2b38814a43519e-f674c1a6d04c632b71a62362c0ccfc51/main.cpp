#include <stdio.h>

int main()
{
    short    checksum=0;
    FILE*    fp=0;

    fp = fopen("save.sav", "r");

    fseek(fp, 0x100, SEEK_SET);
    while(!feof(fp))
    {
        checksum += fgetc(fp);
    }

    printf("The checksum is: %d.\n", checksum);

    fclose(fp);
}